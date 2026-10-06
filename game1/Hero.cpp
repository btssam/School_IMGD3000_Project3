//System includes
#include <math.h>
//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "UI.h"
#include "DisplayManager.h"
//Game includes
#include "Hero.h"
#include "GameOver.h"
#include "Enemy.h"
#include "Fountain.h"
#include "Clue.h"
#include "ColorClue.h"
#include "Keypad.h"


Hero::Hero(UI* p_ui, Map* p_map) {
    this->p_ui = p_ui;
    this->p_map = p_map;

    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    setType("Hero");

    isFacingWall = false;
    isFighting = false;
    
    gridPosition = df::Vector(0, 0);

    move_slowdown = 16;
    move_countdown = move_slowdown;

    take_damage_slowdown = 60;
    take_damage_countdown = take_damage_slowdown;

    facingDirection = Direction::NORTH;

    p_map->updateView(gridPosition, facingDirection);

    p_ui->setHeroPosition(gridPosition);
    updateFountains();
    updateClues();
    updateColorClues();
}

Hero::~Hero(){
    
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
    return 0;
}

void Hero::kbd(const df::EventKeyboard *p_keyboard_event){
    switch(p_keyboard_event->getKey()){
        case df::Keyboard::Q: //quit. May want to expand this to go to a pause menu or main menu later
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

        //to silence warnings about not defining every single key
        default:
            break;
    }
}

void Hero::move_up(){
    //check if allowed to move (e.g. fighting)
    if (isFighting){
        p_ui->addLogMessage("I can't run!");
        return;
    }
    //see if its time to move (check cooldown). throttles movement so its not too fast
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    Room* p_current_room = p_map->getRoom(gridPosition.getX(), gridPosition.getY());

    if (p_current_room != nullptr){
        if (facingDirection == Direction::NORTH) isFacingWall = p_current_room->getIsNorthWall();
        else if (facingDirection == Direction::EAST)  isFacingWall = p_current_room->getIsEastWall();
        else if (facingDirection == Direction::SOUTH) isFacingWall = p_current_room->getIsSouthWall();
        else if (facingDirection == Direction::WEST)  isFacingWall = p_current_room->getIsWestWall();
    }

    if (isFacingWall) {
        take_damage(1);
        p_ui->addLogMessage("I hit a WALL. Ow!");
        return;
    }

    switch (facingDirection) {
    case Direction::NORTH:
        p_ui->addLogMessage("I move NORTH");
        gridPosition.setY(gridPosition.getY() - 1);
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
    updateFountains();
    updateClues();
    updateColorClues();
    updateKeypads();
}

void Hero::turn_left(){
    //check if allowed to move (e.g. fighting)
    if (isFighting){
        p_ui->addLogMessage("I can't run!");
        return;
    }
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
    updateFountains();
    updateClues();
    updateColorClues();
    updateKeypads();
}


void Hero::turn_right(){
    //check if allowed to move (e.g. fighting)
    if (isFighting){
        p_ui->addLogMessage("I can't run!");
        return;
    }
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
    updateFountains();
    updateClues();
    updateColorClues();
    updateKeypads();
}

void Hero::step(){
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;

    //check if a combat is happening and start it if so
    checkCombat();

    if (isFighting) {
        df::ObjectList enemies = WM.objectsOfType("enemy");
        //periodically cause the enemy to damage the player
        take_damage_countdown--;
        if (take_damage_countdown < 0)
            take_damage_countdown = 0;
        
        if (take_damage_countdown == 0){
            take_damage(5);
            p_ui->addLogMessage("Clayhead attacks!");
            take_damage_countdown = take_damage_slowdown;
        }
        
        if (enemies.getCount() == 0) {
            isFighting = false;
        }
    }
}

void Hero::take_damage(int amount){
    p_ui->setHP(std::max(0, p_ui->getHP() - amount));
    if (p_ui->getHP() <= 0){
        p_ui->addLogMessage("I am dead!");
        new GameOver;
        WM.markForDelete(this);
    }
    p_ui->addLogMessage("I take " + std::to_string(amount) + " damage!");
    DM.shake(4, 4, 8);
}

// Checks for combat and spawns enemies and objects
// this function is doing too much and/or needs to be renamed
void Hero::checkCombat() {
    // Already fighting so don't need to start combat
    if (isFighting)
        return;

    // Get room the Hero is in
    Room* p_current_room = p_map->getRoom(
        gridPosition.getX(),
        gridPosition.getY()
    );

    if (p_current_room == nullptr)
        return ;

    // Spawn enemy in room
    if (p_current_room->getHasEnemy()){
        isFighting = true;
        new Enemy();
        //maybe a brief intro or message with a pause to give a chance for the player to get ready
        p_ui->addLogMessage("A Clayhead appears!");
        p_ui->addLogMessage("FIGHT!");
        //could just pause for 2 seconds here to give player a sec to orient themselves
        
        //mark room as cleared as soon as fight starts, so that the player can't just leave and come back to fight the same enemy again (could also be handled at the end of a fight, but since theres no way of running, it doesnt matter)
        p_current_room->setHasEnemy(false);
    }

    // Spawn fountain in room
    if (p_current_room->getHasFountain()) {
        Fountain* p_fountain = new Fountain();

        p_fountain->setRoomPosition(gridPosition);
        p_fountain->setWall(p_current_room->getFountainWall());

        // Mark room so the fountain isn't spawned again
        p_current_room->setHasFountain(false);
    }

    // Spawn clue in room
    if (p_current_room->getHasClue()) {
        Clue* p_clue = new Clue(p_current_room->getClueSprite());

        p_clue->setRoomPosition(gridPosition);
        p_clue->setWall(p_current_room->getClueWall());

        p_current_room->setHasClue(false);

        updateClues();
    }

    // Spawn color clue in room
    if (p_current_room->getHasColorClue()) {
        ColorClue* p_clue = new ColorClue();

        p_clue->setRoomPosition(gridPosition);
        p_clue->setWall(p_current_room->getColorClueWall());

        p_current_room->setHasColorClue(false);

        updateColorClues();
    }

    if (p_current_room->getHasKeypad()){
        Keypad* p_keypad = new Keypad();

        p_keypad->setRoomPosition(gridPosition);
        p_keypad->setWall(p_current_room->getKeypadWall());

        p_current_room->setHasKeypad(false); //dont spawn duplicates
        updateKeypads();
    }
}

void Hero::updateFountains() {
    df::ObjectList fountains = WM.objectsOfType ("Fountain");

    for (int i = 0; i < fountains.getCount(); i++) {
        Fountain* p_fountain = dynamic_cast<Fountain*>(fountains[i]);

        if (p_fountain != nullptr) {
            p_fountain->updateVisibility(gridPosition, facingDirection);
        }
    }
}

void Hero::updateClues() {
    df::ObjectList clues = WM.objectsOfType("Clue");

    for (int i = 0; i < clues.getCount(); i++) {
        Clue* p_clue = dynamic_cast<Clue*>(clues[i]);

        if (p_clue != nullptr) {
            p_clue->updateVisibility(gridPosition, facingDirection);
        }
    }
}

void Hero::updateColorClues() {
    df::ObjectList clues = WM.objectsOfType("ColorClue");

    for (int i = 0; i < clues.getCount(); i++) {
        ColorClue* p_clue = dynamic_cast<ColorClue*>(clues[i]);

        if (p_clue != nullptr)
            p_clue->updateVisibility(gridPosition, facingDirection);
    }
}

void Hero::updateKeypads() {
    df::ObjectList keypads = WM.objectsOfType("Keypad");

    for (int i = 0; i < keypads.getCount(); i++) {
        Keypad* p_keypad = dynamic_cast<Keypad*>(keypads[i]);

        if (p_keypad != nullptr) {
            p_keypad->updateVisibility(gridPosition, facingDirection);
        }
    }
}