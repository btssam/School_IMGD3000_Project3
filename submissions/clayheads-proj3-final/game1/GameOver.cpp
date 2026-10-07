//Engine includes
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
//Game includes
#include "GameOver.h"
#include "GameStart.h"

GameOver::GameOver(){
    setType("GameOver");

    if (setSprite("gameover") == 0)
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    else
        time_to_live = 0;

    setPosition(df::Vector(40.5, 8.5));
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
        if (p_o->getType() == "Map" || p_o->getType() == "Hero" || p_o->getType() == "UI" || p_o->getType() == "enemy" || p_o->getType() == "Reticle" || p_o->getType() == "Fountain" || p_o->getType() == "Clue" || p_o->getType() == "ColorClue" || p_o->getType() == "Keypad" || p_o->getType() == "KeypadButton")
            WM.markForDelete(p_o);
        if (p_o->getType() == "GameStart"){
            p_o->setActive(true);
            dynamic_cast <GameStart *> (p_o)->playMusic(); //resume start music
        }
    }
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