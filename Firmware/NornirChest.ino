#include "arduino_secrets.h"

#include <Adafruit_NeoPixel.h>
#include <Servo.h>

// ============================================================
// Pin assignments
// ============================================================

const byte TOTEM_LED_1_PIN = 2;
const byte TOTEM_LED_2_PIN = 3;
const byte TOTEM_LED_3_PIN = 4;

const byte BRAZIER_RING_PIN = 5;
const byte CHEST_RINGS_PIN  = 6;

const byte ENCODER_CLK_PIN = 7;
const byte ENCODER_DT_PIN  = 8;

const byte LEFT_SERVO_PIN  = 9;
const byte RIGHT_SERVO_PIN = 10;

const byte REED_SWITCH_PIN = 12;
const byte BELL_LED_PIN    = 13;
const byte PIEZO_PIN       = A0;

// D11 is not used.
// The rotary encoder switch is intentionally disconnected.

// ============================================================
// LED settings
// ============================================================

const byte CHEST_RING_COUNT = 3;
const byte PIXELS_PER_RING = 7;
const byte CHEST_PIXEL_COUNT = CHEST_RING_COUNT * PIXELS_PER_RING;

// Set this to 7 if you have one brazier ring.
// Set it to 14 if two brazier rings are chained together.
const byte BRAZIER_PIXEL_COUNT = 14;

const byte LED_BRIGHTNESS = 80;

Adafruit_NeoPixel chestPixels(
  CHEST_PIXEL_COUNT,
  CHEST_RINGS_PIN,
  NEO_GRB + NEO_KHZ800
);

Adafruit_NeoPixel brazierPixels(
  BRAZIER_PIXEL_COUNT,
  BRAZIER_RING_PIN,
  NEO_GRB + NEO_KHZ800
);

// ============================================================
// Servo settings
// ============================================================

Servo leftServo;
Servo rightServo;

// Adjust these angles for your physical lock mechanism.
const int LEFT_LOCKED_ANGLE   = 20;
const int LEFT_UNLOCKED_ANGLE = 110;

const int RIGHT_LOCKED_ANGLE   = 160;
const int RIGHT_UNLOCKED_ANGLE = 70;

// ============================================================
// Rotary encoder settings
// ============================================================

// Change this if your encoder has a different number of detents.
const int ENCODER_DETENTS_PER_REVOLUTION = 20;

// The three rune positions around the totem.
const int RUNE_ANGLES[] = {
  0,
  120,
  240
};

const byte NUMBER_OF_RUNES = 3;

// A rune is accepted within 5 degrees of its target angle.
const int ANGLE_CLEARANCE = 5;

int lastCLKState = HIGH;
long encoderDetents = 0;
bool encoderHasMoved = false;

// ============================================================
// Bell settings
// ============================================================

const int PIEZO_THRESHOLD = 180;
const unsigned long BELL_COOLDOWN_MS = 700;

unsigned long lastBellTrigger = 0;

// ============================================================
// Game state
// ============================================================

bool brazierSolved = false;
bool bellSolved = false;
bool totemSolved = false;
bool chestUnlocked = false;

// ============================================================
// Colors
// ============================================================

uint32_t lockedRuneColor;
uint32_t brazierActiveColor;
uint32_t flashColor;
uint32_t offColor;

// ============================================================
// Setup
// ============================================================

void setup() {
  Serial.begin(9600);

  // Ordinary LEDs
  pinMode(TOTEM_LED_1_PIN, OUTPUT);
  pinMode(TOTEM_LED_2_PIN, OUTPUT);
  pinMode(TOTEM_LED_3_PIN, OUTPUT);
  pinMode(BELL_LED_PIN, OUTPUT);

  // Rotary encoder
  pinMode(ENCODER_CLK_PIN, INPUT_PULLUP);
  pinMode(ENCODER_DT_PIN, INPUT_PULLUP);

  // Reed switch
  // The reed switch should connect D12 to GND when activated.
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);

  // Start encoder reading
  lastCLKState = digitalRead(ENCODER_CLK_PIN);

  // Initialize NeoPixels
  chestPixels.begin();
  brazierPixels.begin();

  chestPixels.setBrightness(LED_BRIGHTNESS);
  brazierPixels.setBrightness(LED_BRIGHTNESS);

  lockedRuneColor = chestPixels.Color(255, 70, 0);
  brazierActiveColor = brazierPixels.Color(255, 0, 0);
  flashColor = chestPixels.Color(255, 255, 255);
  offColor = chestPixels.Color(0, 0, 0);

  // Initialize servos
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  lockChest();

  clearBrazier();
  updateTotemLEDs(-1);
  updateChestRunes();

  Serial.println(F("Nornir Chest ready."));
  Serial.println(F("Solve the brazier, bell, and rotating totem."));
}

// ============================================================
// Main loop
// ============================================================

void loop() {
  if (chestUnlocked) {
    return;
  }

  checkBrazier();
  checkBell();
  checkTotem();

  if (brazierSolved && bellSolved && totemSolved) {
    unlockChest();
  }
}

// ============================================================
// Brazier
// ============================================================

void checkBrazier() {
  bool magnetDetected = digitalRead(REED_SWITCH_PIN) == LOW;

  if (magnetDetected && !brazierSolved) {
    brazierSolved = true;

    Serial.println(F("Brazier solved."));

    setAllBrazierPixels(brazierActiveColor);
    completeSeal(0);
  }
}

// ============================================================
// Bell
// ============================================================

void checkBell() {
  if (bellSolved) {
    return;
  }

  int piezoValue = analogRead(PIEZO_PIN);

  if (piezoValue >= PIEZO_THRESHOLD &&
      millis() - lastBellTrigger >= BELL_COOLDOWN_MS) {

    lastBellTrigger = millis();
    bellSolved = true;

    Serial.print(F("Bell solved. Piezo value: "));
    Serial.println(piezoValue);

    digitalWrite(BELL_LED_PIN, HIGH);
    completeSeal(1);
  }
}

// ============================================================
// Rotary encoder
// ============================================================

void checkTotem() {
  int currentCLKState = digitalRead(ENCODER_CLK_PIN);

  // Read one edge of the encoder's CLK signal.
  if (currentCLKState != lastCLKState && currentCLKState == LOW) {
    if (digitalRead(ENCODER_DT_PIN) != currentCLKState) {
      encoderDetents++;
    } else {
      encoderDetents--;
    }

    encoderDetents = wrapEncoderPosition(encoderDetents);
    encoderHasMoved = true;

    int currentAngle = getEncoderAngle();
    int selectedRune = findMatchingRune(currentAngle);

    Serial.print(F("Totem angle: "));
    Serial.print(currentAngle);
    Serial.print(F(" degrees, selected rune: "));
    Serial.println(selectedRune);

    updateTotemLEDs(selectedRune);

    // Require the user to rotate the totem at least once.
    // This prevents the chest from solving immediately at startup.
    if (encoderHasMoved && selectedRune >= 0 && !totemSolved) {
      totemSolved = true;

      Serial.println(F("Totem solved."));
      completeSeal(2);
    }
  }

  lastCLKState = currentCLKState;
}

long wrapEncoderPosition(long position) {
  while (position >= ENCODER_DETENTS_PER_REVOLUTION) {
    position -= ENCODER_DETENTS_PER_REVOLUTION;
  }

  while (position < 0) {
    position += ENCODER_DETENTS_PER_REVOLUTION;
  }

  return position;
}

int getEncoderAngle() {
  long angle = encoderDetents * 360L;
  angle /= ENCODER_DETENTS_PER_REVOLUTION;

  return angle;
}

int getAngleDifference(int firstAngle, int secondAngle) {
  int difference = abs(firstAngle - secondAngle);

  // Correctly handles the wraparound between 359 and 0 degrees.
  if (difference > 180) {
    difference = 360 - difference;
  }

  return difference;
}

int findMatchingRune(int currentAngle) {
  for (byte i = 0; i < NUMBER_OF_RUNES; i++) {
    int difference = getAngleDifference(
      currentAngle,
      RUNE_ANGLES[i]
    );

    if (difference <= ANGLE_CLEARANCE) {
      return i;
    }
  }

  return -1;
}

void updateTotemLEDs(int selectedRune) {
  digitalWrite(
    TOTEM_LED_1_PIN,
    selectedRune == 0 ? HIGH : LOW
  );

  digitalWrite(
    TOTEM_LED_2_PIN,
    selectedRune == 1 ? HIGH : LOW
  );

  digitalWrite(
    TOTEM_LED_3_PIN,
    selectedRune == 2 ? HIGH : LOW
  );
}

// ============================================================
// Chest rune LEDs
// ============================================================

void updateChestRunes() {
  setChestRing(
    0,
    brazierSolved ? offColor : lockedRuneColor
  );

  setChestRing(
    1,
    bellSolved ? offColor : lockedRuneColor
  );

  setChestRing(
    2,
    totemSolved ? offColor : lockedRuneColor
  );

  chestPixels.show();
}

void setChestRing(byte ringNumber, uint32_t color) {
  int firstPixel = ringNumber * PIXELS_PER_RING;

  for (byte i = 0; i < PIXELS_PER_RING; i++) {
    chestPixels.setPixelColor(firstPixel + i, color);
  }
}

void flashChestRing(
  byte ringNumber,
  byte numberOfFlashes,
  int delayTime
) {
  for (byte flash = 0; flash < numberOfFlashes; flash++) {
    setChestRing(ringNumber, flashColor);
    chestPixels.show();
    delay(delayTime);

    setChestRing(ringNumber, offColor);
    chestPixels.show();
    delay(delayTime);
  }
}

void completeSeal(byte ringNumber) {
  flashChestRing(ringNumber, 3, 130);
  setChestRing(ringNumber, offColor);
  chestPixels.show();
}

// ============================================================
// Brazier LEDs
// ============================================================

void setAllBrazierPixels(uint32_t color) {
  for (byte i = 0; i < BRAZIER_PIXEL_COUNT; i++) {
    brazierPixels.setPixelColor(i, color);
  }

  brazierPixels.show();
}

void clearBrazier() {
  setAllBrazierPixels(offColor);
}

// ============================================================
// Servos and chest lock
// ============================================================

void lockChest() {
  leftServo.write(LEFT_LOCKED_ANGLE);
  rightServo.write(RIGHT_LOCKED_ANGLE);

  Serial.println(F("Chest locked."));
}

void unlockChest() {
  chestUnlocked = true;

  Serial.println(F("All seals solved."));
  Serial.println(F("Unlocking chest."));

  // Celebration flash
  for (byte flash = 0; flash < 3; flash++) {
    for (int i = 0; i < CHEST_PIXEL_COUNT; i++) {
      chestPixels.setPixelColor(i, flashColor);
    }

    chestPixels.show();
    delay(180);

    for (int i = 0; i < CHEST_PIXEL_COUNT; i++) {
      chestPixels.setPixelColor(i, offColor);
    }

    chestPixels.show();
    delay(180);
  }

  // Move the locks to the open position.
  leftServo.write(LEFT_UNLOCKED_ANGLE);
  rightServo.write(RIGHT_UNLOCKED_ANGLE);

  // Leave the brazier lit.
  setAllBrazierPixels(brazierActiveColor);

  // Leave all totem and bell LEDs lit.
  digitalWrite(TOTEM_LED_1_PIN, HIGH);
  digitalWrite(TOTEM_LED_2_PIN, HIGH);
  digitalWrite(TOTEM_LED_3_PIN, HIGH);
  digitalWrite(BELL_LED_PIN, HIGH);
}