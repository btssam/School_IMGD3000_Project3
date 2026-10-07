//a simple colored number that displays on the wall
#pragma once

//Engine Includes
#include "Object.h"
//Game Includes
#include "Room.h"

class Clue : public df::Object {
    private:
        //position of the room in the grid where this clue is located
        df::Vector m_roomPosition;
        //which wall the clue is on (NORTH, EAST, SOUTH, WEST)
        Direction m_wall;

    public:
        //constructor
        Clue(std::string spriteLabel);
        //set the room position
        void setRoomPosition(df::Vector roomPosition);
        //get the room position
        df::Vector getRoomPosition() const;
        //set wall direction
        void setWall(Direction wall);
        //get wall direciton
        Direction getWall() const;
        //update the actual display based on direction/room
        void updateVisibility(df::Vector heroRoom, Direction heroDirection);
};