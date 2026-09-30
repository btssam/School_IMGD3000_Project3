#include "GameStart.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "ResourceManager.h"

#include "Saucer.h"
#include "Hero.h"
#include "Points.h"



GameStart::GameStart(){
    setType("GameStart");
    setSprite("gamestart");
    setLocation(df::CENTER_CENTER);

    registerInterest(df::KEYBOARD_EVENT);

    p_music = RM.getMusic("start music");
    playMusic();
}

int GameStart::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::KEYBOARD_EVENT){
        df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
        switch (p_keyboard_event->getKey()){
            case df::Keyboard::P:
                start();
                break;
            case df::Keyboard::Q:
                GM.setGameOver();
                break;
            default:
                break;
        }
        return 1;
    }
    return 0;
}

int GameStart::draw(){
    return df::Object::draw();
}

void GameStart::start(){
    for (int i=0; i<16; i++)
        new Saucer;
    new Hero;

    //UI
    new Points;
    df::ViewObject *p_vo_nuke = new df::ViewObject; //count of nukes
    p_vo_nuke->setLocation(df::TOP_LEFT);
    p_vo_nuke->setViewString("Nukes");
    p_vo_nuke->setValue(1);
    p_vo_nuke->setColor(df::YELLOW);

    df::ViewObject *p_vo_slow = new df::ViewObject; //count of slows
    p_vo_slow->setLocation(df::TOP_CENTER);
    p_vo_slow->setViewString("Slow");
    p_vo_slow->setValue(1);
    p_vo_slow->setColor(df::YELLOW);

    //when game starts, become inactive
    setActive(false);

    //pause start music
    p_music->pause();
}

void GameStart::playMusic(){
    p_music->play();
}