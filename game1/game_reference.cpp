//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Star.h"
#include "GameStart.h"

// Function prototypes
void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 1;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  loadResources();
  populateWorld();

  GM.run();

  // Shut everything down.
  GM.shutDown();
  return 0;
}

void loadResources(void){
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("sprites/ship-spr.txt", "ship");
  RM.loadSprite("sprites/bullet-spr.txt", "bullet");
  RM.loadSprite("sprites/explosion-spr.txt", "explosion");
  RM.loadSprite("sprites/gameover-spr.txt", "gameover");
  RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
  RM.loadSprite("sprites/saucer-spr-blue.txt", "saucer-blue");

  RM.loadSound("sounds/fire.wav", "fire");
  RM.loadSound("sounds/explode.wav", "explode");
  RM.loadSound("sounds/nuke.wav", "nuke");
  RM.loadSound("sounds/game-over.wav", "game over");

  RM.loadMusic("sounds/start-music.wav", "start music");
}

void populateWorld(void){
  for (int i=0; i<16; i++)
    new Star;
  
  new GameStart();

}