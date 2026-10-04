//Engine includes
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
//Game includes
#include "GameOver.h"

GameOver::GameOver(){
    setType("GameOver");

    if (setSprite("gameover") == 0)
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    else
        time_to_live = 0;

    setLocation(df::CENTER_CENTER);
    registerInterest(df::STEP_EVENT);

    // Remove reticle immediately so combat stops
    df::ObjectList reticles = WM.objectsOfType("Reticle");
    for (int i = 0; i < reticles.getCount(); i++) {
        df::Object* p_reticle = reticles[i];
        WM.markForDelete(p_reticle);
    }

}

GameOver::~GameOver(){
    //remove objects, re-activate gamestart
    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i<object_list.getCount(); i++){
        df::Object *p_o = object_list[i];
        if (p_o->getType() == "Map" || p_o->getType() == "Hero" || p_o->getType() == "UI" || p_o->getType() == "enemy" || p_o->getType() == "Reticle")
            WM.markForDelete(p_o);
        //to be implemented later, making it restart to the start screen instead of just quitting:
        // if (p_o->getType() == "GameStart"){
        //     p_o->setActive(true);
        //     dynamic_cast <GameStart *> (p_o)->playMusic(); //resume start music
        // }
    }
    GM.setGameOver(true); //reset game over state
}

int GameOver::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

void GameOver::step(){
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

int GameOver::draw(){
    return df::Object::draw();
}