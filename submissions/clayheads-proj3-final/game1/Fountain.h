//interactable item that will heal the player once
#pragma once

//engine includes
#include "Object.h"
//game includes
#include "Room.h"

class Fountain : public df::Object {
    private:
        //true if the fountain has been used and is now empty
        bool m_empty;
        //position of the room in the grid where this fountain is located
        df::Vector m_roomPosition;
        //which wall the fountain is on (NORTH, EAST, SOUTH, WEST)
        Direction m_wall;
    public:
        //constructor
        Fountain();
        //use the fountain, healing and making it empty
        void use();
        //check if the fountain is empty
        bool isEmpty() const;
        //set hovered state
        void setHovered(bool hovered);
        //set room position
        void setRoomPosition(df::Vector roomPosition);
        //get room position
        df::Vector getRoomPosition() const;
        //set wall direciton
        void setWall(Direction wall);
        //get wall direction
        Direction getWall() const;
        //update the actual display based on direction/room
        void updateVisibility(df::Vector heroRoom, Direction heroDirection);
};