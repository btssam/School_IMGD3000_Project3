#include "Room.h"


Room::Room(){
    isWallNorth = false;
    isWallEast = false;
    isWallSouth = false;
    isWallWest = false;

    northSprite = "";
    eastSprite = "";
    southSprite = "";
    westSprite = "";

    gridPosition = df::Vector(0, 0);
}

void Room::setWalls(bool north, bool east, bool south, bool west) {
    isWallNorth = north;
    isWallEast = east;
    isWallSouth = south;
    isWallWest = west;
}

// Setters
void Room::setNorthSpriteString(std::string sprite) { northSprite = sprite; }

void Room::setEastSpriteString(std::string sprite)  { eastSprite = sprite; }

void Room::setSouthSpriteString(std::string sprite) { southSprite = sprite; }

void Room::setWestSpriteString(std::string sprite)  { westSprite = sprite; }

void Room::setGridPosition(df::Vector pos) { gridPosition = pos; }

// Getters
bool Room::getIsNorthWall() const { return isWallNorth; }

bool Room::getIsEastWall() const  { return isWallEast; }

bool Room::getIsSouthWall() const { return isWallSouth; }

bool Room::getIsWestWall() const  { return isWallWest; }

std::string Room::getNorthSprite() const { return northSprite; }

std::string Room::getEastSprite() const  { return eastSprite; }

std::string Room::getSouthSprite() const { return southSprite; }

std::string Room::getWestSprite() const  { return westSprite; }