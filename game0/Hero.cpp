#include "Hero.h"
#include "Bullet.h"
#include "EventNuke.h"
#include "GameOver.h"
#include "EventSlow.h"

#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventView.h"


Hero::Hero() {
    setSprite("ship");
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    registerInterest(df::MSE_EVENT);
    setType("Hero");
    df::Vector p(7, WM.getBoundary().getVertical()/2);
    setPosition(p);

    dy = 0;
    move_slowdown = 2;
    move_countdown = move_slowdown;
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    nuke_count = 1;
    slow_count = 1;

    p_reticle = new Reticle();
    p_reticle->draw();
}

Hero::~Hero(){
    new GameOver;
    WM.markForDelete(p_reticle);

    //explosion on death
    df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
    df::addParticles(df::SPARKS, getPosition(), 4, df::RED);
    df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
}

int Hero::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);

        mouse(p_mouse_event);
        return 1;

    }
    return 0;
}

//take action based on which key was pressed
void Hero::kbd(const df::EventKeyboard *p_keyboard_event){
    switch(p_keyboard_event->getKey()){
        case df::Keyboard::Q: //quit
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                WM.markForDelete(this);
            break;
        case df::Keyboard::W: //up
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                dy -= 1;
            if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
                dy += 1;
            break;
        case df::Keyboard::S: //down
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                dy += 1;
            if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
                dy -= 1;
            break;
        case df::Keyboard::SPACE:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
                nuke();
            break;
        case df::Keyboard::LEFTSHIFT:
        case df::Keyboard::RIGHTSHIFT:
            if (p_keyboard_event->getKeyboardAction() ==df::KEY_RELEASED)
                slow();
            break;
        //to silence warnings about not defining every single key
        default:
            break;
    }
}


void Hero::move(int dy){
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    //if staying in window, allow movement
    df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
    if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical()-1))
        WM.moveObject(this, new_pos);
}

void Hero::step(){
    move_countdown--;
    fire_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
    
    if (dy)
        move(dy);
    
    if (fire_countdown < 0)
        fire_countdown = 0;
}

void Hero::fire(df::Vector target){
    if (fire_countdown > 0)
        return;
    fire_countdown = fire_slowdown;
    //fire bullet toward target, compute normalized vector then scale
    df::Vector v = target - getPosition();
    v.normalize();
    v.scale(1);
    Bullet *p = new Bullet(getPosition());
    p->setVelocity(v);

    df::Sound *p_sound = RM.getSound("fire");
    if (p_sound)
        p_sound->play();
}

void Hero::mouse(const df::EventMouse *p_mouse_event){
    if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
        fire(p_mouse_event->getMousePosition());
}

void Hero::nuke() {
    if (!nuke_count)
        return;
    //make nuke event and send to interested objects
    EventNuke nuke;
    WM.onEvent(&nuke);
    nuke_count--;
    //send view event with nukes to viewobject
    df::EventView ev("Nukes", -1, true);
    WM.onEvent(&ev);

    df::Sound *p_sound = RM.getSound("nuke");
    if (p_sound)
        p_sound->play();
}

void Hero::slow(){
    if (!slow_count)
        return;
    EventSlow slow;
    WM.onEvent(&slow);
    slow_count--;
    df::EventView ev("Slow", -1, true);
    WM.onEvent(&ev);

    df::Sound *p_sound = RM.getSound("nuke");
    if (p_sound)
        p_sound->play();

}