# QL-Space-Invaders
Space Invaders for the Sinclair QL - Work in Progress!

![image](https://github.com/SimonGreenaway/QL-Space-Invaders/assets/29223933/080551cf-4edd-4535-9a8f-254d970d4302)


Written in C68/xtc and uses treble buffered (!) sprites. Sprites are fully masked with the background and can be any size that is a multiple of 4 pixels for x, or anything for height. Data is pre-shifted into pixel locations for speed. 8 colour mode only is supported.

Currently a WIP demo - invaders move across and down, ship moves (cursor keys) and flying saucers randomly appear and move across the screen.

Proably needs more RAM than the stock 128k as it uses 2x32k screen buffers.

Executable and sprite library is in 'invaders.zip'. Copy to a floppy and unzip under QDOS, as per usual for the QL.
