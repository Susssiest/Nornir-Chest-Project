# Nornir Chest – Interactive 3D Printable Model

A fully interactive 3D-printable Nornir Chest inspired by *God of War Ragnarök*.

What started as a simple idea for a glowing-rune display piece evolved into a much larger project with sensors, LEDs, and servos that recreate the seal mechanics from the game.

## Project Overview

In *God of War Ragnarök*, Nornir Chests are unlocked by activating three seals. There are four types of seals in the game:

- **Brazier** – activated by setting it on fire  
- **Bell** – activated by ringing it  
- **Rotating Totem** – activated by rotating it to the correct position  
- **Statue** – activated by breaking it  

When a seal is activated, the corresponding rune on the chest flashes and then stops glowing. Once all three runes are deactivated, the chest unlocks.

This model recreates that experience using real sensors and electronics.

### Planned Versions

| Version              | Description                                      | Approx. Filament |
|----------------------|--------------------------------------------------|------------------|
| **Full Interactive** | Sensors, LEDs, servos, Arduino                   | ~1.5 kg         |
| **Pure Print**       | No electronics, no base or seals – pure replica  | ~300 g          |
| **Lamp Version**     | Simplified version with LEDs + batteries only    | Lightweight     |

---

## Electronics

The breadboard, Arduino Nano, and battery pack all sit inside the base.

### Main Components

- **Arduino Nano** (powered via USB-C)
- **3× WS2812B LED rings** (7 LEDs each) – one in each chest rune slot
- **1× WS2812B LED ring** – red glow under the brazier
- **2× Servos** – lock the lid closed
- **Rotary encoder** – rotating totem
- **Reed switch** – brazier (detects magnetic Blades of Chaos)
- **Piezo disk** – bell
- **3× single LEDs** – illuminate the runes on the totem
- **1× single LED** – Bell indicator
- **4× AA battery pack** – powers all LEDs and servos

### Seal Details

**Brazier**  
Uses a reed switch to detect the magnetic Blades of Chaos inserted into the coals. An LED ring under the reed switch glows red when activated. The coals are printed with low infill and fewer walls so light can shine through.

**Rotating Totem**  
A rotary encoder tracks the rotation of the pole. The pole is connected to a hollow cylinder with three different runes. As it rotates, three LEDs on the side of the pole light the correct rune.

**Bell**  
A piezo disk detects vibration when the bell is rung. A dedicated LED lights the corresponding rune.

All wires run down through the stand into the base.

---

## Pin Assignment (Arduino Nano)

| Component                          | Connection              | Nano Pin | Notes |
|------------------------------------|-------------------------|----------|-------|
| Chest Rune LED Rings (3× WS2812B)  | Data                    | D6       | Can be chained together |
| Brazier Red LED Ring (WS2812B)     | Data                    | D5       | Glows red when activated |
| Totem LEDs (3×)                    | Anode via 220 Ω         | D2, D3, D4 | One LED per rune face |
| Bell LED                           | Anode via 220 Ω         | D13      | Lights the Bell rune |
| Servo Left                         | Signal                  | D9       | Lid lock |
| Servo Right                        | Signal                  | D10      | Lid lock |
| Rotary Encoder                     | CLK                     | D7       | |
|                                    | DT                      | D8       | |
|                                    | SW (optional)           | D11      | |
| Reed Switch (Brazier)              | One side                | D12      | Other side → GND (`INPUT_PULLUP`) |
| Piezo Disk (Bell)                  | Positive                | A0       | Negative → GND |
| 4× AA Battery Pack                 | +                       | LED & Servo VCC | **Do not** connect to Nano 5V |
|                                    | –                       | Common GND | |
| USB-C                              |                         | Nano USB | Powers the Arduino only |

---

## Wiring Diagram
┌─────────────────────┐
│   Arduino Nano      │
│                     │
Reed Switch ────►│ D12                 │
│                     │
Piezo (+) ──────►│ A0                  │
│                     │
Encoder CLK ────►│ D7                  │
Encoder DT  ────►│ D8                  │
Encoder SW  ────►│ D11 (optional)      │
│                     │
Totem LED 1 ────►│ D2  (+ 220 Ω)       │
Totem LED 2 ────►│ D3  (+ 220 Ω)       │
Totem LED 3 ────►│ D4  (+ 220 Ω)       │
│                     │
Brazier Ring ───►│ D5  (Data)          │
Chest Rings ────►│ D6  (Data)          │
│                     │
Servo Left  ────►│ D9                  │
Servo Right ────►│ D10                 │
│                     │
Bell LED ───────►│ D13 (+ 220 Ω)       │
└─────────────────────┘

text### Power Connections
4×AA Battery Pack (+) ──┬── VCC of all WS2812B rings
├── VCC of both servos
├── Anodes of the 3 Totem LEDs (via 220 Ω)
└── Anode of the Bell LED (via 220 Ω)
4×AA Battery Pack (–) ──┬── GND of all LEDs, servos, and sensors
└── Arduino Nano GND
USB-C ──────────────────── Arduino Nano only

text> **Important Notes**
> - Connect the battery negative and the Nano’s GND together (common ground is required).
> - Never power the servos or WS2812B LEDs from the Nano’s 5V pin — they draw too much current.
> - A 100–1000 µF capacitor across the LED power rails is recommended to reduce voltage spikes.

---

## Status

The design is complete and ready for testing and final assembly.  
I’m looking forward to building the full interactive version once the project is funded.
