#include "Room.h"


void Room::setCurrentSprite(){
    setSprite("");
}

void Room::setNorthSpriteString(std::string sprite){
    northSprite = sprite;
}

void Room::setEastSpriteString(std::string sprite){
    eastSprite = sprite;
}

void Room::setSouthSpriteString(std::string sprite){
    southSprite = sprite;
}

void Room::setWestSpriteString(std::string sprite){
    westSprite = sprite;
}

Room::Room(){
    setType("Room");
    setCurrentSprite();
}

Room::~Room(){

}

