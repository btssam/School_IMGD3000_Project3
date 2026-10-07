//Engine includes
#include "DisplayManager.h"
//Game includes
#include "ColorClue.h"

ColorClue::ColorClue() {
    setType("ColorClue");

    m_roomPosition = df::Vector(0, 0);
    m_wall = Direction::NORTH;

    setPosition(df::Vector(40, 11));
    setVisible(false);

    setAltitude(2);
}

void ColorClue::setRoomPosition(df::Vector roomPosition) {
    m_roomPosition = roomPosition;
}

df::Vector ColorClue::getRoomPosition() const {
    return m_roomPosition;
}

void ColorClue::setWall(Direction wall) {
    m_wall = wall;
}

Direction ColorClue::getWall() const {
    return m_wall;
}

void ColorClue::updateVisibility(df::Vector heroRoom, Direction heroDirection) {
    if (heroRoom == m_roomPosition && heroDirection == m_wall)
        setVisible(true);
    else
        setVisible(false);
}

int ColorClue::draw() {
    if (!isVisible())
        return 0;

    DM.drawString(df::Vector(38, 11), "#", df::CENTER_JUSTIFIED, df::BLUE);
    DM.drawString(df::Vector(40, 11), "#", df::CENTER_JUSTIFIED, df::YELLOW);
    DM.drawString(df::Vector(42, 11), "#", df::CENTER_JUSTIFIED, df::GREEN);
    DM.drawString(df::Vector(44, 11), "#", df::CENTER_JUSTIFIED, df::RED);

    return 0;
}