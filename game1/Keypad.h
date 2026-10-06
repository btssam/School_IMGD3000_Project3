// Keypad. Houses all the key buttons
#pragma once

#include <vector>

#include "Object.h"

#include "Room.h"
#include "KeypadButton.h"


class Keypad: public df:: Object{
    private:
        //grid-based room position
        df::Vector m_roomPosition;
        //what direction the wall is in
        Direction m_wall;
        //whether it is already solved or not
        bool m_is_solved;
        //current code
        std::string m_entered_code;
        //buttons list
        std::vector<KeypadButton*> m_buttons;

    public:
        //constructor
        Keypad();
        //destructor
        ~Keypad();
        //set grid position of keypad
        void setRoomPosition(df::Vector roomPosition);
        //get grid position of keypad
        df::Vector getRoomPosition() const;
        //set wall direction
        void setWall(Direction wall);
        //get wall direction
        Direction getWall() const;
        //toggles visibility based on hero position and direction
        void updateVisibility(df::Vector heroRoom, Direction heroDirection);
        //draw override
        int draw() override;
        //handle button clicked
        void handleButtonPress(std::string label);
};