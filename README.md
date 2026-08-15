
# Nornir Chest from *God of War Ragnarök*

<img width="1240" height="755" alt="Whole Project" src="https://github.com/user-attachments/assets/a11c25b0-e23d-434e-84f5-f1ce79681e36" />

My goal for this project changed a lot over time. At first, I just wanted to make a model of a 3D-printable Nornir Chest with LEDs or some kind of light so the runes would glow. But it quickly evolved into something much bigger, and I ended up putting far more work into it than I expected.

I’m new to the world of Arduino, PCBs, soldering, and electronics, but I quickly realized I could incorporate it into my model. In *God of War Ragnarök*, you must activate three seals to unlock the chest. There are four seal types in the game: a brazier that activates when set on fire, a bell that activates when rung, a pole that unlocks when rotated correctly, and a statue that activates when it breaks.

When a seal is broken, the chest’s corresponding rune flashes white and then stops glowing. Once all three runes are deactivated, the chest can open and you can retrieve the reward.

My model uses several different sensors to imitate the seals, including a **reed switch**, a **rotary encoder**, and a **piezo disk**. The chest itself has **LED rings** inside the rune slots and **two servos** to lock it. The model will be 3D printed in multiple colors and will use around 1.5 kg of filamenT.

I also plan to make two additional versions of the model:

- A **fully 3D-printable replica** of the chest with no electronics slots, no base, and no seals, using around 300 g of filament.
- A **simplified lamp version** that follows my original idea more closely, using only LEDs and batteries for a much less complicated but still attractive build.

I’m really happy with how the project turned out, and I’m looking forward to building it if it gets funded.

## Electronics

This project uses a variety of electronics to recreate the Nornir Chest mechanics from *God of War Ragnarök*. Since I’m still relatively new to microcontrollers, I will be using a breadboard.

The breadboard sits inside the base, next to mounts for the battery pack and an **Arduino Nano**. The chest itself contains three **WS2812B LED rings** with 7 pixels each, one in each rune slot, plus two servos — one on each side — that keep the lid locked closed.

## Seals

### Brazier
The most complex seal. A reed switch detects the magnetic *Blades of Chaos* when they are inserted into a hole in the coals. An LED ring sits just below the reed switch and glows red when the seal is activated. The coals are printed with low infill and fewer wall loops so light can shine through. A separate LED ring illuminates the corresponding rune on the chest.

### Rotating Pole
My personal favorite. A rotary encoder tracks the rotation of the pole. The pole is connected to a hollow cylinder with three different runes printed on three sides. As the pole turns, the correct rune faces forward and is illuminated by three LEDs mounted on the side of the pole.

### Rune Bell
A piezo disk detects the vibration when the bell is rung. A single LED lights the corresponding rune.

All wiring runs down into the base. Power is split between an external 4× AA battery holder** in the base, which supplies the servos and LEDs, and a USB-C cable that powers the Arduino Nano.

## Credits

- [Blades of Chaos fridge magnet](https://makerworld.com/en/models/3068479-blades-of-chaos-fridge-magnet#profileId-3454054) — Used as the magnetic Blades of Chaos inserted into the brazier. It is meant to be a fridge magnet.
- [Stone formation base](https://makerworld.com/en/models/2541501-stoneformation-15?from=search#profileId-2798135) — This is the rocky base I used. I modified it to have a central port for all the electronics and indents to connect the chest and three seals.
- [HW-040 module case housing enclosure](https://makerworld.com/en/models/1896813-hw-040-module-case-housing-enclosure?from=search#profileId-2032305) — This is the enclosure I used for the rotary encoder.
- [Print-in-place hinge set](https://makerworld.com/en/models/791901-print-in-place-hinge-set?from=search#profileId-730453) — This is the hinge I used. I modified it to have extruded pins and be much smaller.

## Updates

- Added a fully 3D-printable version.

## Get .blend File Here
(I'm also a noob to github lol. I can't figure out how to upload large files.)

https://drive.google.com/file/d/1p0lWug-2twfeMgqFWuvS9LOxBlz-mlpI/view?usp=sharing


## Updated BOM

<img width="1066" height="472" alt="Screenshot 2026-08-14 at 5 10 53 PM" src="https://github.com/user-attachments/assets/daeb57f7-734c-46ce-97fb-86468f2cc218" />



