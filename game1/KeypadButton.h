//Interactable individual keypad button objects.
#pragma once

#include <string>

#include "Object.h"

class Keypad;

class KeypadButton : public df::Object {
    private:
        //label
        std::string m_label;
        //pointer to the parent keypad object
        Keypad* m_p_parent;
        //if currently hovered, true
        bool m_is_hovered;

    public:
        //constructor
        KeypadButton(std::string label, df::Vector position, Keypad* p_parent);
        //set hovered state
        void setHovered(bool hovered);
        //get hovered state
        bool isHovered() const;
        //handle click
        void click();
        //draw override;
        int draw() override;
};