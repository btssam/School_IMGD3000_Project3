#include "Fountain.h"

Fountain::Fountain() {
    setType("Fountain");

    // Starts full
    m_empty = false;
    setSprite("fountain");

    // Sets position
    m_roomPosition = df::Vector(0, 0);
    m_wall = Direction::NORTH;
    setPosition(df::Vector(40, 11));

    setAltitude(2);
}

void Fountain::use() {
    // Empty fountains can't be used again
    if (m_empty)
        return;

    m_empty = true;
    setSprite("fountain-empty");
}

bool Fountain::isEmpty() const {
    return m_empty;
}

void Fountain::setHovered(bool hovered) {
    // An empty fountain stays empty when hovered over
    if (m_empty) {
        setSprite("fountain-empty");
    }
    else if (hovered) {
        setSprite("fountain-hover");
    }
    else {
        setSprite("fountain");
    }
}

void Fountain::setRoomPosition(df::Vector roomPosition) {
    m_roomPosition = roomPosition;
}

df::Vector Fountain::getRoomPosition() const {
    return m_roomPosition;
}

void Fountain::setWall(Direction wall) {
    m_wall = wall;
}

Direction Fountain::getWall() const {
    return m_wall;
}

void Fountain::updateVisibility(df::Vector heroRoom, Direction heroDirection) {
    if (heroRoom == m_roomPosition && heroDirection == m_wall)
        setVisible(true);
    else
        setVisible(false);
}