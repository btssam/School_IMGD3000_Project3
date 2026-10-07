//
// game1.cpp - Dungeon Crawler starter
//

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
// Game includes
#include "Hero.h"
#include "Map.h"
#include "UI.h"
#include "Reticle.h"
#include "Enemy.h"
#include "Fountain.h"
#include "GameStart.h"

//function prototypes
void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[]) {
    //start up game manager
    if (GM.startUp() != 0) {
        LM.writeLog("Error starting game manager!");
        return 1;
    }

    //flush logfile
    LM.setFlush(true);

    //load sprites, sounds, etc.
    loadResources();

    //add the UI, map, hero, etc.
    populateWorld();

    GM.run();

    GM.shutDown();
    return 0;
}

void loadResources(void) {
    //ui sprite
    if (RM.loadSprite("sprites/ui.txt", "ui") != 0) {
        LM.writeLog("Error loading UI sprite");
    }

    //reticle sprite
    RM.loadSprite("sprites/reticle.txt", "reticle");

    //minimap
    RM.loadSprite("sprites/map_1_3x3.txt", "map-3x3");
    RM.loadSprite("sprites/map_1_8x5.txt", "map-8x5");
    RM.loadSprite("sprites/map_1_8x16.txt", "map-8x16");

    //wall sprites
    RM.loadSprite("sprites/wall_1.txt", "wall-1");
    RM.loadSprite("sprites/wall_2.txt", "wall-2");
    RM.loadSprite("sprites/wall_3.txt", "wall-3");
    RM.loadSprite("sprites/wall_4.txt", "wall-4");

    //hallway sprites
    RM.loadSprite("sprites/hallway_1.txt", "hallway-1");
    RM.loadSprite("sprites/hallway_2.txt", "hallway-2");
    RM.loadSprite("sprites/hallway_3.txt", "hallway-3");
    RM.loadSprite("sprites/hallway_4.txt", "hallway-4");

    //game over sprite
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");

    //gamestart sprite
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    //story sprite
    RM.loadSprite("sprites/story.txt", "story");

    //enemy sprites
    RM.loadSprite("sprites/enemy.txt", "enemy");
    RM.loadSprite("sprites/enemy-hit.txt", "enemy-hit");
    RM.loadSprite("sprites/boss.txt", "boss");
    RM.loadSprite("sprites/boss-hit.txt", "boss-hit");

    //fountain sprites
    RM.loadSprite("sprites/fountain.txt", "fountain");
    RM.loadSprite("sprites/fountain-hover.txt", "fountain-hover");
    RM.loadSprite("sprites/fountain-empty.txt", "fountain-empty");

    //clue sprites
    RM.loadSprite("sprites/clue-9.txt", "clue-9");
    RM.loadSprite("sprites/clue-6.txt", "clue-6");
    RM.loadSprite("sprites/clue-2.txt", "clue-2");
    RM.loadSprite("sprites/clue-7.txt", "clue-7");

    //keypad sprites
    RM.loadSprite("sprites/keypad_base.txt", "keypad_base");
    RM.loadSprite("sprites/keypad_button.txt", "keypad_button");

    //claypool victory sprites
    RM.loadSprite("sprites/claypool_base.txt", "claypool_base");
    RM.loadSprite("sprites/claypool_clay.txt", "claypool_clay");
    RM.loadSprite("sprites/claypool_X.txt", "claypool_X");
    RM.loadSprite("sprites/claypool_sparkles.txt", "claypool_sparkles");

    //player hurt sound
    RM.loadSound("audio/hurt.wav", "hurt");
    //player turn sound
    RM.loadSound("audio/turn.wav", "turn");
    //player step sound
    RM.loadSound("audio/step.wav", "step");
    //player click sound
    RM.loadSound("audio/sword.wav", "sword");
    //enemy damage sound
    RM.loadSound("audio/enemy-damage.wav", "enemy-damage");
    //enemy death sound
    RM.loadSound("audio/enemy-death.wav", "enemy-death");
    //boss damage sound
    RM.loadSound("audio/boss-damage.wav", "boss-damage");
    //boss death sound
    RM.loadSound("audio/boss-death.wav", "boss-death");
    //drink fountain sound
    RM.loadSound("audio/drink.wav", "drink");
    //press keypad sound
    RM.loadSound("audio/keypad.wav", "keypad");
    //keypad correct code sound
    RM.loadSound("audio/keypad-correct.wav", "keypad-correct");
    //keypad incorrect code sound
    RM.loadSound("audio/keypad-incorrect.wav", "keypad-incorrect");

    //Title screen music
    RM.loadMusic("audio/music-title.wav", "music-title");
    //Exposition screen music
    RM.loadMusic("audio/music-exposition.wav", "music-exposition");
    //Explore music
    RM.loadMusic("audio/music-explore.wav", "music-explore");
    //Enemy combat music
    RM.loadMusic("audio/music-enemy.wav", "music-enemy");
    //Boss combat music
    RM.loadMusic("audio/music-boss.wav", "music-boss");
    //Gameover music
    RM.loadMusic("audio/music-gameover.wav", "music-gameover");
    //Win music
    RM.loadMusic("audio/music-win.wav", "music-win");
}

void populateWorld(void) {
    new GameStart();
}
