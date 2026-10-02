#ifndef UI_H
#define UI_H

#include "Object.h"
#include <string>
#include <vector>
#include "Vector.h"

class UI : public df::Object {
    private:
        int m_hp;
        int m_max_hp;
        std::vector<std::string> m_log;

        df::Vector m_hero_pos;
        std::string m_map_sprite_label;

    public:
        UI();

        int draw() override;
        int eventHandler(const df::Event* p_e) override;

        void setHP(int hp);
        int getHP() const;

        void addLogMessage(std::string message);

        void setHeroPosition(df:: Vector pos);
        void setMapSprite(std::string sprite_label);
};

#endif