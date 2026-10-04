// System includes
#include <string>
//Engine includes
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "ObjectList.h"
//Game includes
#include "Reticle.h"
#include "UI.h"
#include "Enemy.h"

//should probably be removed when not fighting an enemy
Reticle::Reticle() {
    setType("Reticle");

    setSprite("reticle");

    setSolidness(df::SPECTRAL);

    setAltitude(df::MAX_ALTITUDE);

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
        const df::EventMouse*p_mouse_event =
            dynamic_cast<const df::EventMouse*>(p_e);

        if (p_mouse_event == nullptr)
            return 0;

        // Move reticle with mouse
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }

        // Click on enemy
        if (p_mouse_event->getMouseAction() == df::CLICKED &&
            p_mouse_event->getMouseButton() == df::Mouse::LEFT) {
                df::Vector click_position = p_mouse_event->getMousePosition();

                df::ObjectList objects = WM.objectsAtPosition(click_position);

                for (int i = 0; i < objects.getCount(); i++) {
                    df::Object* p_object = objects[i];

                    if (p_object->getType() == "enemy") {
                        Enemy* p_enemy =
                            dynamic_cast<Enemy*>(p_object);

                        if (p_enemy != nullptr) {
                            //might want an enemy take damage function to allow different values
                            p_enemy->setHP(p_enemy->getHP() - 5);
                            p_enemy->flash();

                            df::ObjectList ui_list = WM.objectsOfType("UI");

                            if (ui_list.getCount() > 0) {
                                UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

                                if (p_ui != nullptr) {
                                    p_ui->addLogMessage(
                                        "Clayhead hit! HP:" + std::to_string(p_enemy->getHP())
                                    );
                                }
                            }

                            // Enemy death
                            if (p_enemy->getHP() <= 0) {
                                df::ObjectList ui_list = WM.objectsOfType("UI");

                                if (ui_list.getCount() > 0) {
                                    UI* p_ui = dynamic_cast<UI*>(ui_list[0]);

                                    if (p_ui != nullptr) {
                                        p_ui->addLogMessage("Clayhead defeated!");
                                    }
                                }

                                WM.markForDelete(p_enemy);
                            }
                        }
                        return 1;
                    }
                }
                return 1;
            }
        }
    return 0;
}