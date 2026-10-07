#include "DisplayManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "Keypad.h"
#include "Map.h"
#include "UI.h"

Keypad::Keypad(){
    setType("Keypad");
    setSprite("keypad_base");

    m_roomPosition = df::Vector(0,0);
    m_wall = Direction::NORTH;
    m_is_solved = false;
    m_entered_code = "";

    //center in dungeon view, above UI
    setPosition(df::Vector(40, 8));
    setAltitude(1);
    setVisible(false);

    struct ButtonLayout{
        std::string label;
        df::Vector pos;
    };

    ButtonLayout layout[] = {
        {"7", df::Vector(28, 3.5)}, {"8", df::Vector(40, 3.5)}, {"9", df::Vector(52, 3.5)},
        {"4", df::Vector(28, 6.5)}, {"5", df::Vector(40, 6.5)}, {"6", df::Vector(52, 6.5)},
        {"1", df::Vector(28, 9.5)}, {"2", df::Vector(40, 9.5)}, {"3", df::Vector(52, 9.5)},
        {"CLEAR", df::Vector(28, 12.5)},                   {"ENTER", df::Vector(52, 12.5)}
    };

    for (const ButtonLayout& item : layout){
        KeypadButton* p_btn = new KeypadButton(item.label, item.pos, this);
        m_buttons.push_back(p_btn);
    }

}

Keypad::~Keypad(){
    df::WorldManager* p_wm = &df::WorldManager::getInstance();
    for (KeypadButton* p_btn : m_buttons){
        if (p_btn != nullptr){
            p_wm->markForDelete(p_btn);
        }
    }
}

void Keypad::setRoomPosition(df::Vector roomPosition){
    m_roomPosition = roomPosition;
}

df::Vector Keypad::getRoomPosition() const{
    return m_roomPosition;
}

void Keypad::setWall(Direction wall){
    m_wall = wall;
}

Direction Keypad::getWall() const{
    return m_wall;
}

void Keypad::updateVisibility(df::Vector heroRoom, Direction heroDirection){
    //only visibile when standing in keypad's room and facing the wall it is on
    if(heroRoom == m_roomPosition && heroDirection == m_wall){
        setVisible(true);
    } else {
        setVisible(false);
    }

    for (KeypadButton* p_btn : m_buttons){
        if (p_btn != nullptr){
            p_btn->setVisible(isVisible());
        }
    }
}

int Keypad::draw(){
    if (!isVisible()){
        return 0;
    }
    // draw base sprite. just functions as a black blank background
    df::Object::draw();
    //draw the entered digit on bottom of the keypad display
    df::DisplayManager* p_dm = &df::DisplayManager::getInstance();
    std::string display_text = m_entered_code.empty() ? "_ _ _ _": m_entered_code;
    p_dm->drawString(df::Vector(40, 13), display_text, df::CENTER_JUSTIFIED, df::YELLOW);

    return 0;
}

void Keypad::handleButtonPress(std::string label){
    if (m_is_solved) {
        return;
    }
    if (label == "CLEAR"){
        //add sound
        df::Sound* p_sound = RM.getSound("keypad");
        if (p_sound != nullptr)
            p_sound->play();

        m_entered_code.clear();

    } else if (label == "ENTER"){
        if (m_entered_code == "9627"){
            m_is_solved = true;

            //add sound
            df::Sound* p_sound = RM.getSound("keypad-correct");
            if (p_sound != nullptr)
                p_sound->play();

            df::WorldManager* p_wm = &df::WorldManager::getInstance();
            df::ObjectList maps = p_wm->objectsOfType("Map");

            if (maps.getCount() > 0){
                Map* p_map = dynamic_cast<Map*>(maps[0]);
                if (p_map != nullptr){
                    //get keypad room
                    Room *p_room = p_map->getRoom(m_roomPosition.getX(), m_roomPosition.getY());
                    if (p_room != nullptr){
                        //open the wall
                        p_room->setWalls(false, false, true, false);
                        p_room->setEastSpriteString("hallway-3");
                        p_map->updateView(m_roomPosition, m_wall);
                    }
                }
            }
            //close keypad
            setVisible(false);
            for (KeypadButton* p_btn : m_buttons){
                if (p_btn != nullptr){
                    p_btn->setVisible(false);
                }
            }   
            p_wm->markForDelete(this);

            df::ObjectList ui_list = p_wm->objectsOfType("UI");
            if (ui_list.getCount() > 0){
                UI* p_ui = dynamic_cast<UI*>(ui_list[0]);
                if (p_ui != nullptr){
                    p_ui->addLogMessage("Wall slides open!");
                }
            }

        } else {
            //add sound
            df::Sound* p_sound = RM.getSound("keypad-incorrect");
            if (p_sound != nullptr)
                p_sound->play();

            m_entered_code.clear();
        }
    } else {
        //digit entered
        if (m_entered_code.length() < 4){
            m_entered_code += label;
        }
    }
}