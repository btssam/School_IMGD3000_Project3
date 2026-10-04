#IMGD3000 - A26
#10/04/26
#Project 3 - Alpha

==============================================================
1. Team Information
Team Name: Clayheads
Team Members:
Benjamin Samara (bsamara@wpi.edu)
Austin Peterson (apeterson1@wpi.edu)
==============================================================

2. Platforms:
Linux (Fedora KDE Plasma Desktop 44)
Mac OS
This project was built to run on either platform

==============================================================
3. Files:
clayheads-proj3-alpha/
├── README.txt
├── VIDEOLINK.txt
├── AI-PROMPTS.txt
├── Makefile
├── *.h
├── *.cpp
├── df-font.ttf
├──sprites
  ├── *.txt

==============================================================
3. Code Structure:
Hero: handles input, player movement, and player states
Map & Room: handle grid data and changing the viewpoint backgrounds
Enemy & Recticle: handle combat and mouse interaction
UI: handles updating HUD display, like the log, HP, and minimap
GameOver: handles clean up/endscreen on Hero death

==============================================================
4. Compiling and Running:
cd clayheads-proj3-alpha/
make
./game1
To clean :
make clean

==============================================================
5. Controls and Instructions:
W/UP: move up
A/LEFT: turn left
D/RIGHT: turn right
LEFT-CLICK: attack enemy
Q: close the window

In this alpha version, there is a maze with an enemy at the end. You will get a game over if your HP reaches zero and you can defeat the enemy by clicking on it. This functions as the victory state, though the game will continue playing after defeating the enemy, and you can simply close the window when you've defeated the enemy, with the Q key.
==============================================================