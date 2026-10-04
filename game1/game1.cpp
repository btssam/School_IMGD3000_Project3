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

    //enemy sprites
    RM.loadSprite("sprites/enemy.txt", "enemy");
    RM.loadSprite("sprites/enemy-hit.txt", "enemy-hit");

}

void populateWorld(void) {
    // populate UI
    UI* p_ui = new UI();

    //currently just spawns reticle and enemy right away, will want to add some logic actually have enemies positioned on the map
    // populate reticle
    new Reticle();

    // populate map
    Map* p_map = new Map();
    // populate hero
    new Hero(p_ui, p_map);

    // populate enemy
    // new Enemy();
}
