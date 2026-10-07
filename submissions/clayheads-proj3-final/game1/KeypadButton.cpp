//engine includes
#include "DisplayManager.h"
#include "ResourceManager.h"
//game includes
#include "Keypad.h"
#include "KeypadButton.h"

KeypadButton::KeypadButton(std::string label, df::Vector position, Keypad* p_parent){
    setType("KeypadButton");
    setSprite("keypad_button");

    //manually stop animation from cycling through frames
    df::Animation anim = getAnimation();
    anim.setSlowdownCount(-1);
    anim.setIndex(0);
    setAnimation(anim);

    m_label = label;
    m_p_parent = p_parent;
    m_is_hovered = false;

    setPosition(position);
    setAltitude(2);
    setVisible(false);
}

void KeypadButton::setHovered(bool hovered){
    if (m_is_hovered == hovered){
        return;
    }
    m_is_hovered = hovered;

    //put hovered above others
    setAltitude(hovered ? 3 : 2);

    //switch between frame 0 and frame 1 (which is a bit larger)
    df::Animation anim = getAnimation();
    anim.setSlowdownCount(-1);
    anim.setIndex(hovered ? 1 : 0);
    setAnimation(anim);
}

bool KeypadButton::isHovered() const{
    return m_is_hovered;
}

void KeypadButton::click(){
    //add sound
    df::Sound* p_sound = RM.getSound("keypad");
    if (p_sound != nullptr)
        p_sound->play();
    
    if (m_p_parent != nullptr){
        m_p_parent->handleButtonPress(m_label);
    }
};

int KeypadButton::draw(){
    if (!isVisible()) return 0;

    //draw the button sprite
    df::Object::draw();

    //draw the label centered on the button
    df::DisplayManager* p_dm = &df::DisplayManager::getInstance();
    df::Vector text_pos(getPosition().getX(), getPosition().getY() + 0.5f);
    p_dm->drawString(text_pos, m_label, df::CENTER_JUSTIFIED, df::YELLOW);

    return 0;
}
    