This is a Portable Radio Arduino project, but with a twist, it is controller by "gestures" read from a IR sensor.
It features two displays: a 7-segment display to show the current status/ action and a LCD display to show the name of the song.
The "gestures" that the IR reads are the following:
  - Detect an object for a second to play next song.
  - Detect an object for two seconds to play previous song.
  - Detect an object for three seconds to loop / restart current song.
  - Detect an object for more than three seconds to pause the song, until released.
If no object is detected, music will continue playing.

Songs are loaded in a MicroSD card.
It also features a hidden button that plays a "vine-boom" SFX when held. If it's pressed once it will lower the volume, press again to raise the volume.

This project uses the following components:
 - Ardunino UNO R3.
 - MDF RobotPlayer.
 - Any compatible speaker.
 - A MicroSD card.
 - Jumper wires (<30).
 - A BreadBoard.
 - IR sensor (Digital-input).

Will update later with more information.
