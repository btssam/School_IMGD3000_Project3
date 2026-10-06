//Game includes
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

    hasEnemy = false;
    hasFountain = false;
    // fountains default to North walls
    fountainWall = Direction::NORTH;

    hasClue = false;
    clueSprite = "";
    clueWall = Direction::NORTH;
    hasColorClue = false;
    colorClueWall = Direction::SOUTH;

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
void Room::setHasEnemy(bool enemy) {hasEnemy = enemy;}
void Room::setHasFountain(bool fountain) {hasFountain = fountain;}

// Getters
bool Room::getIsNorthWall() const { return isWallNorth; }
bool Room::getIsEastWall() const  { return isWallEast; }
bool Room::getIsSouthWall() const { return isWallSouth; }
bool Room::getIsWestWall() const  { return isWallWest; }
std::string Room::getNorthSprite() const { return northSprite; }
std::string Room::getEastSprite() const  { return eastSprite; }
std::string Room::getSouthSprite() const { return southSprite; }
std::string Room::getWestSprite() const  { return westSprite; }
bool Room::getHasEnemy() {return hasEnemy;}
bool Room::getHasFountain() {return hasFountain;}
void Room::setFountainWall(Direction wall) {fountainWall = wall;}
Direction Room::getFountainWall() const {return fountainWall;}
void Room::setHasClue(bool clue) {hasClue = clue;}
bool Room::getHasClue() {return hasClue;}
void Room::setClueSprite(std::string sprite) {clueSprite = sprite;}
std::string Room::getClueSprite() const {return clueSprite;}
void Room::setClueWall(Direction wall) {clueWall = wall;}
Direction Room::getClueWall() const {return clueWall;}
void Room::setHasColorClue(bool clue) {hasColorClue = clue;}
bool Room::getHasColorClue() {return hasColorClue;}
void Room::setColorClueWall(Direction wall) {colorClueWall = wall;}
Direction Room::getColorClueWall() const {return colorClueWall;}