#ifndef COLORCLUE_H
#define COLORCLUE_H

#include "Object.h"
#include "Room.h"

class ColorClue : public df::Object {
    private:
        df::Vector m_roomPosition;
        Direction m_wall;

    public:
        ColorClue();

        void setRoomPosition(df::Vector roomPosition);
        df::Vector getRoomPosition() const;

        void setWall(Direction wall);
        Direction getWall() const;

        void updateVisibility(df::Vector heroRoom, Direction heroDirection);

        int draw() override;
};

#endif