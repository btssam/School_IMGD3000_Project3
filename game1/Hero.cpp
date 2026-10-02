#include "Hero.h"
#include "GameOver.h"

#include "LogManager.h"
#include "WorldManager.h"
// #include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
// #include "EventView.h"
#include "UI.h"
#include <math.h>
#include "DisplayManager.h"


Hero::Hero(UI* p_ui, Map* p_map) {
    this->p_ui = p_ui;
    this->p_map = p_map;

    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    // registerInterest(df::MSE_EVENT);
    setType("Hero");

    isFacingWall = false;
    // isFighting = false;
    
    gridPosition = df::Vector(0, 0);

    move_slowdown = 16;
    move_countdown = move_slowdown;

    facingDirection = Direction::NORTH;


    p_map->updateView(gridPosition, facingDirection);

    p_ui->setHeroPosition(gridPosition);

    // fire_slowdown = 15;
    // fire_countdown = fire_slowdown;

    // p_reticle = new Reticle();
    // p_reticle->draw();
}

Hero::~Hero(){
    new GameOver;
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
        case df::Keyboard::Q: //quit
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) //just on pressed, not on released
                GM.setGameOver(true);
            break;
        case df::Keyboard::W:
        case df::Keyboard::UPARROW:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                move_up();
            break;
        case df::Keyboard::A:
        case df::Keyboard::LEFTARROW:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                turn_left();
            break;
        case df::Keyboard::D:
        case df::Keyboard::RIGHTARROW:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
                turn_right();
            break;
        //consider adding back to move backwards?

        // TEST to see if health decreases by pressing "h"
        case df::Keyboard::H:
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                take_damage(10);
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
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    Room* p_current = p_map->getRoom(gridPosition.getX(), gridPosition.getY());
    isFacingWall = false;

    if (p_current != nullptr){
        if (facingDirection == Direction::NORTH) isFacingWall = p_current->getIsNorthWall();
        else if (facingDirection == Direction::EAST)  isFacingWall = p_current->getIsEastWall();
        else if (facingDirection == Direction::SOUTH) isFacingWall = p_current->getIsSouthWall();
        else if (facingDirection == Direction::WEST)  isFacingWall = p_current->getIsWestWall();
    }

    if (isFacingWall) {
        p_ui->addLogMessage("I hit a WALL. Ow!");
        return;
    }

    switch (facingDirection) {
    case Direction::NORTH:
        p_ui->addLogMessage("I move NORTH");
        gridPosition.setY(gridPosition.getY() - 1); //might want a setter for this, to confirm if within map bounds
        break;
    case Direction::EAST:
        p_ui->addLogMessage("I move EAST");
        gridPosition.setX(gridPosition.getX() + 1);
        break;
    case Direction::SOUTH:
        p_ui->addLogMessage("I move SOUTH");
        gridPosition.setY(gridPosition.getY() + 1);
        break;
    case Direction::WEST:
        p_ui->addLogMessage("I move WEST");
        gridPosition.setX(gridPosition.getX() - 1);
        break;
    }

    p_ui->setHeroPosition(gridPosition);
    p_map->updateView(gridPosition, facingDirection);
}



void Hero::turn_left(){
    //check if allowed to move (e.g. fighting)
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    switch (facingDirection) {
    case Direction::NORTH:
        facingDirection = Direction::WEST;
        p_ui->addLogMessage("I turn left: WEST");
        break;
    case Direction::WEST:
        facingDirection = Direction::SOUTH;
        p_ui->addLogMessage("I turn left: SOUTH");
        break;
    case Direction::SOUTH:
        facingDirection = Direction::EAST;
        p_ui->addLogMessage("I turn left: EAST");
        break;
    case Direction::EAST:
        facingDirection = Direction::NORTH;
        p_ui->addLogMessage("I turn left: NORTH");
        break;
    }

    p_map->updateView(gridPosition, facingDirection);


    //update what character currently sees based on facing direction/current room

}


void Hero::turn_right(){
    //check if allowed to move (e.g. fighting)
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    switch (facingDirection) {
    case Direction::NORTH:
        facingDirection = Direction::EAST;
        p_ui->addLogMessage("I turn right: EAST");
        break;
    case Direction::EAST:
        facingDirection = Direction::SOUTH;
        p_ui->addLogMessage("I turn right: SOUTH");
        break;
    case Direction::SOUTH:
        facingDirection = Direction::WEST;
        p_ui->addLogMessage("I turn right: WEST");
        break;
    case Direction::WEST:
        facingDirection = Direction::NORTH;
        p_ui->addLogMessage("I turn right: NORTH");
        break;
    }

    p_map->updateView(gridPosition, facingDirection);


    //update what character currently sees based on facing direction/current room

}

void Hero::step(){
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
}

void Hero::take_damage(int amount){
    p_ui->setHP(std::max(0, p_ui->getHP() - amount));
    p_ui->addLogMessage("I took " + std::to_string(amount) + " damage!");
    DM.shake(4, 4, 8);
    if (p_ui->getHP() <= 0){
        p_ui->addLogMessage("I am dead!");
        WM.markForDelete(this);
    }
}