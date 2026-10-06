// System includes
#include <string>
#include <algorithm>
//Engine includes
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventMouse.h"
#include "ObjectList.h"
//Game includes
#include "Reticle.h"
#include "UI.h"
#include "Enemy.h"
#include "Fountain.h"
#include "KeypadButton.h"

//should probably be removed when not fighting an enemy
Reticle::Reticle() {
    setType("Reticle");
    setSprite("reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(4);
    registerInterest(df::MSE_EVENT);

    float worldWidth = WM.getBoundary().getHorizontal();
    float worldHeight = WM.getBoundary().getVertical();

    setPosition(df::Vector(
        worldWidth / 2,
        worldHeight / 2
    ));
}

int Reticle::draw() {
    return df::Object::draw();
}

int Reticle::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);

        if (p_mouse_event == nullptr)
            return 0;

        // Move reticle with mouse
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            handleMouseMove(p_mouse_event->getMousePosition());
            return 1;
        }

        // Click on object
        if (p_mouse_event->getMouseAction() == df::CLICKED &&
            p_mouse_event->getMouseButton() == df::Mouse::LEFT) {
            handleMouseClick(p_mouse_event->getMousePosition());
            return 1;
        }
    }
    return 0;
}

void Reticle::handleMouseMove(df::Vector mouse_pos) {
    // Moves reticle
    setPosition(mouse_pos);

    //reset hover on all keypad buttons
    df::ObjectList buttons = WM.objectsOfType("KeypadButton");
    for (int i = 0; i < buttons.getCount(); i++){
        KeypadButton* p_button = dynamic_cast<KeypadButton*>(buttons[i]);
        if (p_button != nullptr){
            p_button->setHovered(false);
        }
    }

    //check hover on fountain
    df::ObjectList fountains = WM.objectsOfType("Fountain");
    for (int i = 0; i < fountains.getCount(); i++) {
        Fountain* p_fountain = dynamic_cast<Fountain*>(fountains[i]);
        if (p_fountain != nullptr) {
            p_fountain->setHovered(false);
        }
    }

    // Checks what mouse is on (just fountains for now)
    df::ObjectList objects = WM.objectsAtPosition(mouse_pos);
    for (int i = 0; i < objects.getCount(); i++) {
        Fountain* p_fountain = dynamic_cast<Fountain*>(objects[i]);
        if (p_fountain != nullptr && p_fountain->isVisible()) {
            p_fountain->setHovered(true);
        }
    }

    //hover button
    for (int i = 0; i < objects.getCount(); i++){
        KeypadButton* p_button = dynamic_cast<KeypadButton*>(objects[i]);
        if (p_button != nullptr && p_button->isVisible()){
            p_button->setHovered(true);
        }
    }
}

void Reticle::handleMouseClick(df::Vector click_pos) {
    // If we hit an enemy, stop
    if (checkEnemy(click_pos)) {
        return;
    }

    // Otherwise check for fountain
    checkFountain(click_pos);

    //should be its own function too. check keypad buttons
    df::ObjectList object = WM.objectsAtPosition(click_pos);
    for (int i = 0; i < object.getCount(); i++){
        KeypadButton* p_button = dynamic_cast<KeypadButton*>(object[i]);
        if (p_button != nullptr && p_button->isVisible()){
            p_button->click();
            return;
        }
    }
}

bool Reticle::checkEnemy(df::Vector click_pos) {
    df::ObjectList objects = WM.objectsAtPosition(click_pos);

    // check for visible enemy
    for (int i = 0; i < objects.getCount(); i++) {
        df::Object* p_object = objects[i];

        if (!p_object->isVisible()) {
            continue;
        }

        if (p_object->getType() == "enemy") {
            Enemy* p_enemy = dynamic_cast<Enemy*>(p_object);

            if (p_enemy != nullptr) {
                //might want an enemy take damage function to allow different values
                int new_hp = std::max(0, p_enemy->getHP() - 5);
                p_enemy->setHP(new_hp);
                p_enemy->flash();

                df::ObjectList ui_list = WM.objectsOfType("UI");

                if (ui_list.getCount() > 0) {
                    UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

                    if (p_ui != nullptr) {
                        p_ui->addLogMessage("Clayhead hit! HP:" + std::to_string(p_enemy->getHP()));
                        if (p_enemy->getHP() <= 0) {
                            p_ui->addLogMessage("Clayhead defeated!");
                        }
                    }
                }

                if (p_enemy->getHP() <= 0) 
                    WM.markForDelete(p_enemy);

                return true;
            }
        }
    }

    return false;
}

bool Reticle::checkFountain(df::Vector click_pos) {
    df::ObjectList objects = WM.objectsAtPosition(click_pos);

    // if no enemy hit, check for interactables (fountain)
    for (int i = 0; i < objects.getCount(); i++) {
        df::Object* p_object = objects[i];

        if (!p_object->isVisible()) {
            continue;
        }

        if (p_object->getType() == "Fountain") {
            Fountain* p_fountain = dynamic_cast<Fountain*>(p_object);
            if (p_fountain != nullptr && !p_fountain->isEmpty()) {
                df::ObjectList ui_list = WM.objectsOfType("UI");
                if (ui_list.getCount() > 0) {
                    UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

                    if (p_ui != nullptr) {
                        int new_hp = std::min(p_ui->getHP() + 25, 100);
                        p_ui->setHP(new_hp);
                        p_ui->addLogMessage("Restored 25 HP!");
                    }
                }
                p_fountain->use();
                return true;
            }
        }
    }

    return false;
}

// int Reticle::eventHandler(const df::Event* p_e) {
    
//     if (p_e->getType() == df::MSE_EVENT) {
//         const df::EventMouse*p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);

//         if (p_mouse_event == nullptr)
//             return 0;

//         // Move reticle with mouse
//         if (p_mouse_event->getMouseAction() == df::MOVED) {
//             df::Vector mouse_position = p_mouse_event->getMousePosition();

//             // Moves reticle
//             setPosition(mouse_position);

//             df::ObjectList fountains = WM.objectsOfType("Fountain");
//             for (int i = 0; i < fountains.getCount(); i++) {
//                 Fountain* p_fountain = dynamic_cast<Fountain*>(fountains[i]);
//                 if (p_fountain != nullptr) {
//                     p_fountain->setHovered(false);
//                 }
//             }

//             // Checks what mouse is on
//             df::ObjectList objects = WM.objectsAtPosition(mouse_position);
//             for (int i = 0; i < objects.getCount(); i++) {
//                 Fountain* p_fountain = dynamic_cast<Fountain*>(objects[i]);
//                 if (p_fountain != nullptr && p_fountain->isVisible()) {
//                     p_fountain->setHovered(true);
//                 }
//             }

//             return 1;
//         }

//         // Click on object
//         if (p_mouse_event->getMouseAction() == df::CLICKED &&
//             p_mouse_event->getMouseButton() == df::Mouse::LEFT) {
                
//                 df::Vector click_position = p_mouse_event->getMousePosition();
//                 df::ObjectList objects = WM.objectsAtPosition(click_position);

//                 // check for visible enemy first
//                 for (int i = 0; i < objects.getCount(); i++) {
//                     df::Object* p_object = objects[i];

//                     //skip invisible objects
//                     if(!p_object->isVisible()){
//                         continue;
//                     }

//                     if (p_object->getType() == "enemy") {
//                         Enemy* p_enemy = dynamic_cast<Enemy*>(p_object);

//                         if (p_enemy != nullptr) {
//                             //might want an enemy take damage function to allow different values
//                             int new_hp = std::max(0, p_enemy->getHP() - 5);
//                             p_enemy->setHP(new_hp);
//                             p_enemy->flash();

//                             df::ObjectList ui_list = WM.objectsOfType("UI");

//                             if (ui_list.getCount() > 0) {
//                                 UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

//                                 if (p_ui != nullptr) {
//                                     p_ui->addLogMessage("Clayhead hit! HP:" + std::to_string(p_enemy->getHP()));
//                                     if (p_enemy->getHP() <= 0) {
//                                         p_ui->addLogMessage("Clayhead defeated!");
//                                     }
//                                 }
//                             }

//                             if (p_enemy->getHP() <= 0) 
//                                 WM.markForDelete(p_enemy);

//                             return 1;
//                         }
//                     }
//                 }
//                 // if no enemy hit, check for interactables
//                 for (int i = 0; i < objects.getCount(); i++) {
//                     df::Object* p_object = objects[i];

//                     if (!p_object->isVisible()) {
//                         continue;
//                     }

//                     if (p_object->getType() == "Fountain") {
//                         Fountain* p_fountain = dynamic_cast<Fountain*>(p_object);
//                         if (p_fountain != nullptr && !p_fountain->isEmpty()) {
//                             df::ObjectList ui_list = WM.objectsOfType("UI");
//                             if (ui_list.getCount() > 0) {
//                                 UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

//                                 if (p_ui != nullptr) {
//                                     int new_hp = std::min(p_ui->getHP() + 50, 100);
//                                     p_ui->setHP(new_hp);
//                                     p_ui->addLogMessage("Restored 50 HP!");
//                                 }
//                             }
//                             p_fountain->use();
//                             return 1;
//                         }
//                     }
//                 }
//                 return 1;
//             }
//     }
//     return 1;
// }