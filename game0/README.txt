#IMGD3000 - A26
#08/25/26
#Project 1
#Benjamin Samara (bsamara@wpi.edu)

1. Platform:
Linux.
Specifically, this was built and ran on Fedora 44.

2. Game Mod:
Major Addition/Mod:
-I added a Slow weapon, similar to the nuke (EventSlow.h and EventSlow.cpp - generally the event structure is similar to the nuke)
    -Has a UI in the middle center which displays # of Slows remaining (GameStart.cpp - another ViewObject called p_vo_slow)
    -Activated on hitting left or right shift - reducing the UI value to 0 and causing the effect (Hero.cpp in kbd() and in slow() using variable slow_count)
    -Saucers become slower when used, temporarily, making them easier to shoot (Saucer.cpp - registers and reacts to SLOW_EVENT. Uses variable slow_cooldown for duration, alongside the step() and STEP_EVENT. Slowed via setVelocity())
    -Saucers become cyan and animate more slowly during the same duration (As above, but using the setSprite() function)
        -This is done using a separate saucer sprite file (saucer-spr-blue.txt . only changes are to color and slowdown. Had to update game.cpp to load that sprite)
Minor Polish:
-Updated gamestart-spr.txt to include the new controls instructions (i.e. "Shift slows")
-Shrank the Saucer spawn points (Saucer.cpp moveToStart() function) so that it doesn't get partially get cut off by window if spawning at lowest points
-Removed the Splash Screen, as it was overlapping with the GameStart sprite (game.cpp)

3.How to compile:
cd samara-proj1
make clean
make
./game

4.File Directory Structure (particularly noting what has changed from my mod. * = every other file that was not changed for my mods):
>samara-proj1 (folder)
>>EventSlow.cpp
>>EventSlow.h
>>game.cpp
>>GameStart.cpp
>>Hero.cpp
>>Hero.h
>>Makefile
>>README.txt
>>Saucer.cpp
>>Saucer.h
>>*
>>sounds (folder)
>>>*
>>sprites (folder)
>>>gamestart-spr.txt
>>>saucer-spr-blue.txt
>>>*

5.Anything Else:
N/A

6.Video Link:
https://www.youtube.com/watch?v=POkmeu1VCRw