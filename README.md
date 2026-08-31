
# Nornir Chest from God of War Ragnarök

<img width="1240" height="755" alt="Whole Project" src="https://github.com/user-attachments/assets/a11c25b0-e23d-434e-84f5-f1ce79681e36" />

This is a 3D printable replica model of the Nornir Chest from God of War Ragnarök. My final version uses a variety of electronics to simulate the way the chest works in the game. In God Of War, Nornir Chests are puzzles found throughout the map that use their environments to hide and disguise the activators, or seals. There are 4 types of seals, totem poles, braziers, bells, and viking statues. They each have different activation methods, and each are tied to different runes on the chest. When a seal is activated, the rune on it flashes and disappears, and the corrisponding rune on the chest does the same. I currently have two versions of the chest, a fully printable version, and a fully electronic version with seals.

## The Seals

Brazier - two 7 pixel WS2812B rings, reed switch. Printed gold, black, grey, and blue/transparent PLA.
Totem Pole - 3 dumb LEDs, rotary encoder. Printed in PLA wood, and blue/transparent PLA.
Bell - 1 dumb LED, piezo switch. Printed in PLA wood, gold, and blue/transperent PLA.

## The Chest

The chest uses three 7 pixel WS2812B rings and a servo. The servos turn 90 degrees to lock/unlock the chest, and the LEDs cover the runes. It is hinged, and is printed in multiple parts to avoid changes between the gold, black, grey, and blue/transparent PLA. Any parts that would otherwise be glued are connected via pins.

## The Base

The rocky base is not only a cool base for the chest, it acts as a hub for the electronics. I made room for a breadboard for beginners (like me lol), an Arduino Nano, and a battery pack. All wires go through holes, and they will have some supports in them when you pull them out. I suggest using a paper clip to stick it in and push all of the supports out, it shouldn't be too hard.

## Printing

The chest uses 5 filaments, mostly Sunlu and Bambu Labs. I printed some parts with a 0.2 mm nozzle, such as the hinges, viking head, runes, etc, to preserve small details and improve the accuracy of the prints. I also changed the speed and infill on some parts, for example, the runes are printed in 100% infill grey to let light only through the rune hole, and not be visible through the plastic. I always used glue, and I used a cheap smooth PEI plate I found on amazon.

[Pin layout.csv](https://github.com/user-attachments/files/31162670/Pin.layout.csv)

## Credits

- [Blades of Chaos fridge magnet](https://makerworld.com/en/models/3068479-blades-of-chaos-fridge-magnet#profileId-3454054) — Used as the magnetic Blades of Chaos inserted into the brazier. It is meant to be a fridge magnet.
- [Stone formation base](https://makerworld.com/en/models/2541501-stoneformation-15?from=search#profileId-2798135) — This is the rocky base I used. I modified it to have a central port for all the electronics and indents to connect the chest and three seals.
- [HW-040 module case housing enclosure](https://makerworld.com/en/models/1896813-hw-040-module-case-housing-enclosure?from=search#profileId-2032305) — This is the enclosure I used for the rotary encoder.
- [Print-in-PLAce hinge set](https://makerworld.com/en/models/791901-print-in-PLAce-hinge-set?from=search#profileId-730453) — This is the hinge I used. I modified it to have extruded pins and be much smaller.

## Updates

- Added a fully 3D-printable version.
- Will update firmware to fit physical chest wherever needed.

## Get .blend File Here
(I'm also a noob to github lol. I can't figure out how to upload large files.)

https://drive.google.com/file/d/1p0lWug-2twfeMgqFWuvS9LOxBlz-mlpI/view?usp=sharing


## Updated BOM

<img width="1066" height="472" alt="Screenshot 2026-08-14 at 5 10 53 PM" src="https://github.com/user-attachments/assets/daeb57f7-734c-46ce-97fb-86468f2cc218" />



