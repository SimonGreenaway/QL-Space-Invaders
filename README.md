# QL-Space-Invaders
Space Invaders for the Sinclair QL - Work in Progress!

![image](https://github.com/SimonGreenaway/QL-Space-Invaders/assets/29223933/019bf0c5-803e-442b-9be7-8db43287e013)

![image](https://github.com/SimonGreenaway/QL-Space-Invaders/assets/29223933/16a34f25-7617-48db-83a2-8a0a1f30ee25) ![image](https://github.com/SimonGreenaway/QL-Space-Invaders/assets/29223933/1f7df6c4-9e9a-4578-9536-8a73513f15f6)


Written in C68/xtc and uses triple buffered (!) sprites. Sprites are fully masked with the background and can be any size that is a multiple of 4 pixels for x, or anything for height. Data is pre-shifted into pixel locations for speed. 8 colour mode only is supported. Tested under sQLux, all running under Linux.

Currently a WIP demo - invaders move across and down, ship moves (cursor keys) and flying saucers randomly appear and move across the screen. Space fires a bullet. Invaders can be hit, slowly speeding the remaining up. 'P' pauses the key.

Probably needs more RAM than the stock 128k as it uses 2x32k screen buffers.

Executable and sprite library is in 'invaders.zip'. Copy to a floppy and unzip under QDOS, as per usual for the QL. Execute with: EW flp1_sprite,#1
