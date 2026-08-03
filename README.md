# Nornir Chest From God Of War Ragnarock
  My goal has changed a lot over the course of this project. At first I just wanted to make a cool 3D printable model of a Nornir Chest that had some LEDs in it or some kind of light to make the runes glow. But it quickly evolved into a much bigger project, and I put a lot more work into it then I expected. I'm new to the world of Arduino, PCBs, soldering, etc, but I quickly realized I could implement it in my model. In the game, you have to activate three seals to unlock the chest. There are 4 types of seals in the game, a brazier that activates when set on fire, a bell that activates when rung, a pole that unlocks when it is rotated correctly, and a statue that activates when it breaks. When a seal is broken, the chest's corresponding rune on it's side flashes white and then stops glowing. When all three runes are deactivated, the chest can open, and you can retrieve the reward. My model uses a few different sensors to imitate the seals, including a reed switch, a rotary encoder, and a piezo disk. The chest itself has LED rings inside the rune slots, and 2 servos to lock it. The model will be 3D printed with a few different colors, and amounts to around one and a half kilograms of filament. I plan on also making 2 other versions of the model. I will remove all slots for electronics, and remove the base and seals to make a fully 3D printable replica of the chest that is around 300 grams of filament, and a lamp that aligns with my original idea for the project, that just includes some LEDSs and batteries, a much less complicated, but still very attractive model. I'm very happy with how the project came out and look forwards to building it after it hopefully gets funded.

  <img width="1240" height="755" alt="Whole Project" src="https://github.com/user-attachments/assets/e4af5ea9-ea40-43cc-afae-b2a4e4423496" />


ELECTRONICS

My project uses a variety of electronics to imitate the Nornir Chest from God Of War Ragnarock. I'm a noob in the world of micro controllers, so I'm using a breadboard. The breadboard is the main port for all other electronics, it positioned inside the base, next to mounts for a battery and an arduino nano. The chest has three WS2812B led rings (7 pixels per ring) in each rune slot, and two servos, one on each side, to lock the lid onto the chest. The brazier is by far the most complicated seal, it has a reed switch to sense the magnetic Blades of Chaos, which will be inserted into a hole in the coals, a led ring just below the reed switch to glow red when activated, and a led ring for the rune. The coals will be printed with low infill and less wall loops to let light through. The rotating totem might be my favorite seal, it uses a rotary encoder to detect how the pole is rotated, and as the pole rotates different runes will be displayed. The pole is connected to a hollow cylinder that has three runes on 3 different sides, as the pole rotates, so does the rune cylinder. There are three LEDs mounted on the side of the pole to make each rune glow. The final seal is the bell. It uses a piezo disk to detect vibrations, and a led to light up the rune. All wires go through the stand into the base. I am using an external 4X AA battery holder for the servos and leds, it will be housed inside the base. The microcontroller, an arduino nano, will also be housed in the base, it will use a usbc cable as a power source.



CREDITS:

https://makerworld.com/en/models/3068479-blades-of-chaos-fridge-magnet#profileId-3454054 - Used as the magnetic Blades of Chaos inserted into the brazier. It is meant to be a fridge magnet.

https://makerworld.com/en/models/2541501-stoneformation-15?from=search#profileId-2798135 - This is the rocky base I used. I modified it to have a central port for all the electronics, and indents to connect the chest and 3 seals onto it.

https://makerworld.com/en/models/1896813-hw-040-module-case-housing-enclosure?from=search#profileId-2032305  - This is just a enclosure for the rotary encoder.

https://makerworld.com/en/models/791901-print-in-place-hinge-set?from=search#profileId-730453  - This is the hinge I used. I modified it to have extruded pins, and be much smaller.
  
  UPDATES:

  Added fully 3D printable version.
