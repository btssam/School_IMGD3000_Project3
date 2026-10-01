#ifndef UI_H
#define UI_H

#include "Object.h"
#include <string>
#include <vector>

class UI : public df::Object {
    private:
        int m_hp;
        std::vector<std::string> m_log;

    public:
        UI();

        int draw() override;
        int eventHandler(const df::Event* p_e) override;

        void setHP(int hp);
        int getHP() const;

        void addLogMessage(std::string message);
};

#endif