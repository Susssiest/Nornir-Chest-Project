
## Project Electronics Overview

In *God of War Ragnarök*, Nornir Chests are unlocked by activating three seals. There are four types of seals in the game:

- **Brazier** – activated by being set on fire  
- **Bell** – activated when rung
- **Rotating Totem** – activated by being rotated to the correct position  
- **Statue** – activated by being broken 

When a seal is activated, the corresponding rune on the chest flashes and then stops glowing. Once all three runes are deactivated, the chest unlocks.

This model recreates the in game experience using real sensors and electronics.

### Planned Versions

| Version              | Description                                      | Approx. Filament |
|----------------------|--------------------------------------------------|------------------|
| **Full Interactive** | Sensors, LEDs, servos, Arduino                   | ~1.5 kg         |
| **Pure Print**       | No electronics, no base or seals – pure replica  | ~300 g          |
| **Lamp Version**     | Simplified version with LEDs + batteries only    | Lightweight     |

---

## Base

The breadboard, Arduino Nano, and battery pack all sit inside the base.

### Main Components

- **Arduino Nano** (powered via USB-C)
- **4× WS2812B LED rings** (7 LEDs each) – one in each chest rune slot, and 2 in brazier
- **2× Servos** – lock the lid
- **Rotary encoder** – rotating totem
- **Reed switch** – brazier (detects magnetic Blades of Chaos)
- **Piezo disk** – tracks bell vibration
- **3× single LEDs** – illuminate the runes on the totem
- **1× single LED** – illuminates the rune on the bell
- **4× AA battery pack** – powers all LEDs and servos

### Seal Details

**Brazier**  
Uses a reed switch to detect the magnetic Blades of Chaos inserted into the coals. An LED ring under the reed switch glows red when activated. The coals are printed with low infill and fewer walls so light can shine through. An led ring is also mounted further down in the base to illuminate the rune.

**Rotating Totem**  
A rotary encoder tracks the rotation of the pole. The pole is connected to a hollow cylinder with three different runes. As it rotates, three LEDs on the side of the pole light the correct rune.

**Bell**  
A piezo disk detects vibration when the bell is rung. A dedicated LED lights the corresponding rune.

All wires run down through the stand into the base.

[Pin layout.csv](https://github.com/user-attachments/files/31162670/Pin.layout.csv)
