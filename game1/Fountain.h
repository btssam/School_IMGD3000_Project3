#ifndef FOUNTAIN_H
#define FOUNTAIN_H

#include "Object.h"
#include "Room.h"

class Fountain : public df::Object {
    private:
        bool m_empty;

        df::Vector m_roomPosition;
        Direction m_wall;

    public:
        Fountain();

        void use();
        bool isEmpty() const;

        void setHovered(bool hovered);

        void setRoomPosition(df::Vector roomPosition);
        df::Vector getRoomPosition() const;

        void setWall(Direction wall);
        Direction getWall() const;

        void updateVisibility(df::Vector heroRoom, Direction heroDirection);
};

#endif