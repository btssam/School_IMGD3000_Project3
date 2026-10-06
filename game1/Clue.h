#ifndef CLUE_H
#define CLUE_H

#include "Object.h"
#include "Room.h"

class Clue : public df::Object {
    private:
        df::Vector m_roomPosition;
        Direction m_wall;

    public:
        Clue(std::string spriteLabel);

        void setRoomPosition(df::Vector roomPosition);
        df::Vector getRoomPosition() const;

        void setWall(Direction wall);
        Direction getWall() const;

        void updateVisibility(df::Vector heroRoom, Direction heroDirection);
};

#endif