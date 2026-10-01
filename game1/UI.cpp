#include "UI.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include <string>

UI::UI() {
    setType("UI");

    m_hp = 100;
    m_log.clear();

    int result = setSprite("ui");

    if (result != 0) {
        LM.writeLog("UI: setSprite FAILED");
    }
    else {
        LM.writeLog("UI: setSprite SUCCESS");
    }

    setPosition(df::Vector(40, 20));
}

int UI::draw() {
    int result = df::Object::draw();

    // HP
    DM.drawString(
        df::Vector(3, 20),
        std::to_string(m_hp),
        df::LEFT_JUSTIFIED,
        df::RED
    );

    // Log
    for (int i = 0; i < m_log.size() && i < 3; i++) {
        DM.drawString(
            df::Vector(11, 19.5 + i),
            m_log[i],
            df::LEFT_JUSTIFIED,
            df::WHITE
        );
    }

    return result;
}

void UI::setHP(int hp) {
    m_hp = hp;
}

int UI::getHP() const {
    return m_hp;
}

void UI::addLogMessage(std::string message) {
    // Adds newest log message to the front
    m_log.insert(m_log.begin(), message);

    // Keeps only the 3 most recent messages
    if (m_log.size() > 3) {
        m_log.pop_back();
    }
}

int UI::eventHandler(const df::Event* p_e) {
    return 0;
}