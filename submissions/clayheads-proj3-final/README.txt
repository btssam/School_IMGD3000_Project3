#IMGD3000 - A26
#10/07/26
#Project 3 - Final

==============================================================
1. Team Information
Team Name:
Clayheads
Game Name:
Wasteland: Mark of the Clay Pool
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
├── AI-WRITEUP.txt
├── Design_Doc.pdf
├── game1/
  ├── Makefile
  ├── *.h
  ├── *.cpp
  ├── df-font.ttf
  ├──df-config.txt
  ├──audio
    ├──*.wav
  ├──sprites/
    ├── *.txt
├──dragonfly/

==============================================================
4. Code Structure:
Hero: handles input, player movement, and player states. Detects and renders appropriate object when moving
Map & Room: handle grid data and changing the viewpoint backgrounds
Enemy: spawn enemies and handles combat
UI: handles updating HUD display, like the log, HP, and minimap
Clue/ColorClue: non-interactable clues found throughout to find out keypad code
Fountain: one-time interactable heal
Keypad & KeypadButton: interactable way to input code and reveal final room
Reticle: handles mouse interaction, including fountains, keypads and enemies
GameStart: plays starting screen, story crawl, and handles initializes
GameVictory: similar to gameover, but displays a victory screen
GameOver: handles clean up/endscreen on Hero death or quitting

==============================================================
5. Compiling and Running:
cd clayheads-proj3-alpha/game1
make
./game1
To clean :
make clean

==============================================================
6. Controls and Instructions:
W/UP: move up
A/LEFT: turn left
D/RIGHT: turn right
LEFT-CLICK: attack enemy
Q: quit
P: start game

The player is in a maze, looking for the victory area. They use the clues around the and ultimately input the right code into keypad to unlock the final room. There are enemies placed throughout, and a final boss, which can cause the player to either win or lose.
==============================================================
7. Other information:
This game has a minor Dragondly configuration: it widened and heightened the display window by 2 characters