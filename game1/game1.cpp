//
// game1.cpp - Dungeon Crawler starter
//

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

//game includes
#include "Hero.h"
#include "Map.h"
#include "UI.h"

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
    //ui spirte
    if (RM.loadSprite("sprites/ui.txt", "ui") != 0) {
        LM.writeLog("Error loading UI sprite");
    }

    //minimap
    RM.loadSprite("sprites/map_1_3x3.txt", "map-3x3");

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

}

void populateWorld(void) {
    UI* p_ui = new UI();
    // Log tests
    p_ui->addLogMessage("Message 1 oh yeah");
    p_ui->addLogMessage("Message 2 aw yeah");
    p_ui->addLogMessage("Message 3 let's go");
    p_ui->addLogMessage("Message 4 booyah");

    Map* p_map = new Map();
    new Hero(p_ui, p_map);
}
