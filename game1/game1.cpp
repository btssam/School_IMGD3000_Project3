//
// game1.cpp - Minimal Dragonfly starter
//

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "Object.h"
#include "Vector.h"

// A simple game object that displays a '*' character in the center of the screen
class Star : public df::Object {
public:
    Star() {
        setType("Star");
        setPosition(df::Vector(40, 12));
        registerInterest(df::KEYBOARD_EVENT);
    }

    int draw(void) override {
        return DM.drawCh(getPosition(), '*', df::YELLOW);
    }

    int eventHandler(const df::Event* p_e) override {
        if (p_e->getType() == df::KEYBOARD_EVENT) {
            const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
            if (p_keyboard_event && p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                if (p_keyboard_event->getKey() == df::Keyboard::Q) {
                    GM.setGameOver(true);
                    return 1;
                }
            }
        }
        return 0;
    }
};

int main(int argc, char* argv[]) {
    if (GM.startUp() != 0) {
        LM.writeLog("Error starting game manager!");
        return 1;
    }
    LM.setFlush(true);
    new Star();
    GM.run();
    GM.shutDown();
    return 0;
}
