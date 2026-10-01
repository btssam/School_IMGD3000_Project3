#include "Hero.h"
// #include "GameOver.h"

#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventView.h"


Hero::Hero(UI* p_ui) {
    this->p_ui = p_ui;

    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    // registerInterest(df::MSE_EVENT);
    setType("Hero");

    isFacingWall = false;
    // isFighting = false;
    
    gridPosition = df::Vector(0, 0);

    move_slowdown = 20;
    move_countdown = move_slowdown;

    facingDirection = Direction::NORTH;

    // fire_slowdown = 15;
    // fire_countdown = fire_slowdown;

    // p_reticle = new Reticle();
    // p_reticle->draw();
}

Hero::~Hero(){
    // new GameOver;
    // WM.markForDelete(p_reticle);
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
    // if (p_e->getType() == df::MSE_EVENT) { //will want this for attacking
    //     const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);

    //     mouse(p_mouse_event);
    //     return 1;

    // }
    return 0;
}

//take action based on which key was pressed
void Hero::kbd(const df::EventKeyboard *p_keyboard_event){
    switch(p_keyboard_event->getKey()){
        // case df::Keyboard::Q: //quit
            // if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            //     WM.markForDelete(this);
            // break;
        case df::Keyboard::W: //up
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) //just on pressed, not on released
                move_up();
            break;
        case df::Keyboard::A: //left
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                turn_left();
            break;
        case df::Keyboard::D: //right
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                turn_right();
            break;

        // TEST to see if health decreases by pressing "h"
        case df::Keyboard::H:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                p_ui->setHP(p_ui->getHP() - 10);
            }
            break;

        //to silence warnings about not defining every single key
        default:
            break;
    }
}

void Hero::move_up(){
    //check if allowed to move (e.g. fighting)
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0) //might need to consolidate this countdown check into one function (i.e. not do it for all 3 movement types)
        return;
    move_countdown = move_slowdown;
    printf("I move up\n");

    //update grid position based on facing direction/current room

    switch (facingDirection) {
    case Direction::NORTH:
        printf("I am facing NORTH\n");
        //unsure if I should use -1 for up, like drawing in dragonfly, or +1 for up, like math
        gridPosition.setY(gridPosition.getY() - 1); //might want a setter for this, to confirm if within map bounds
        break;
    case Direction::EAST:
        printf("I am facing EAST\n");
        gridPosition.setX(gridPosition.getX() + 1);
        break;
    case Direction::SOUTH:
        printf("I am facing SOUTH\n");
        gridPosition.setY(gridPosition.getY() + 1);
        break;
    case Direction::WEST:
        printf("I am facing WEST\n");
        gridPosition.setX(gridPosition.getX() - 1);
        break;
    }

    printf("X: %.0f, Y: %.0f\n", gridPosition.getX(), gridPosition.getY());
}



void Hero::turn_left(){
    //check if allowed to move (e.g. fighting)
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    printf("i turn left\n");
    switch (facingDirection) {
    case Direction::NORTH:
        facingDirection = Direction::WEST;
        printf("I am facing WEST\n");
        break;
    case Direction::WEST:
        facingDirection = Direction::SOUTH;
        printf("I am facing SOUTH\n");
        break;
    case Direction::SOUTH:
        facingDirection = Direction::EAST;
        printf("I am facing EAST\n");
        break;
    case Direction::EAST:
        facingDirection = Direction::NORTH;
        printf("I am facing NORTH\n");
        break;
    }

    //update what character currently sees based on facing direction/current room

}


void Hero::turn_right(){
    //check if allowed to move (e.g. fighting)
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    printf("i turn right\n");
    switch (facingDirection) {
    case Direction::NORTH:
        facingDirection = Direction::EAST;
        printf("I am facing EAST\n");
        break;
    case Direction::EAST:
        facingDirection = Direction::SOUTH;
        printf("I am facing SOUTH\n");
        break;
    case Direction::SOUTH:
        facingDirection = Direction::WEST;
        printf("I am facing WEST\n");
        break;
    case Direction::WEST:
        facingDirection = Direction::NORTH;
        printf("I am facing NORTH\n");
        break;
    }

    //update what character currently sees based on facing direction/current room

}

void Hero::step(){
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
}