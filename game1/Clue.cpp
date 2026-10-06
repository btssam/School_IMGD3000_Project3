#include "Clue.h"

Clue::Clue(std::string spriteLabel) {
    setType("Clue");
    setSprite(spriteLabel);

    m_roomPosition = df::Vector(0, 0);
    // Default direction is north
    m_wall = Direction::NORTH;

    setPosition(df::Vector(40, 8));
    setVisible(false);

    setAltitude(2);
}

void Clue::setRoomPosition(df::Vector roomPosition) {
    m_roomPosition = roomPosition;
}

df::Vector Clue::getRoomPosition() const {
    return m_roomPosition;
}

void Clue::setWall(Direction wall) {
    m_wall = wall;
}

Direction Clue::getWall() const {
    return m_wall;
}

void Clue::updateVisibility(df::Vector heroRoom, Direction heroDirection) {
    if (heroRoom == m_roomPosition && heroDirection == m_wall)
        setVisible(true);
    else
        setVisible(false);
}