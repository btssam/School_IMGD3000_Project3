#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "GameStart.h"


GameOver::GameOver(){
    setType("GameOver");

    if (setSprite("gameover") == 0)
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    else
        time_to_live = 0;

    setLocation(df::CENTER_CENTER);
    registerInterest(df::STEP_EVENT);


    df::Sound *p_sound = RM.getSound("game over");
    if (p_sound)
        p_sound->play();
}

GameOver::~GameOver(){
    //remove saucers and view objects, re-activate gamestart
    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i<object_list.getCount(); i++){
        df::Object *p_o = object_list[i];
        if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
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