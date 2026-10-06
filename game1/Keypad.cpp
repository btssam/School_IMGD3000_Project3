#include "DisplayManager.h"

#include "Keypad.h"

Keypad::Keypad(){
    setType("Keypad");
    setSprite("keypad_base");

    m_roomPosition = df::Vector(0,0);
    m_wall = Direction::NORTH;
    m_is_solved = false;
    m_entered_code = "";

    //center in dungeon view, above UI
    setPosition(df::Vector(40, 8));
    setAltitude(2);
    setVisible(false);
}

void Keypad::setRoomPosition(df::Vector roomPosition){
    m_roomPosition = roomPosition;
}

df::Vector Keypad::getRoomPosition() const{
    return m_roomPosition;
}

void Keypad::setWall(Direction wall){
    m_wall = wall;
}

Direction Keypad::getWall() const{
    return m_wall;
}

void Keypad::updateVisibility(df::Vector heroRoom, Direction heroDirection){
    //only visibile when standing in keypad's room and facing the wall it is on
    if(heroRoom == m_roomPosition && heroDirection == m_wall){
        setVisible(true);
    } else {
        setVisible(false);
    }
}

int Keypad::draw(){
    if (!isVisible()){
        return 0;
    }
    //draw base sprite
    df::Object::draw();
    //draw the entered digit on bottom of the keypad display
    df::DisplayManager* p_dm = &df::DisplayManager::getInstance();
    std::string display_text = m_entered_code.empty() ? "_ _ _ _": m_entered_code;
    p_dm->drawString(df::Vector(40, 13), display_text, df::CENTER_JUSTIFIED, df::YELLOW);

    return 0;
}