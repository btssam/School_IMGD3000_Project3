#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "EventStep.h"

class Enemy : public df::Object {
    private:
        int m_hp;
        int m_moveCooldown;
        int m_move_countdown;
        int m_flash;
        int m_flash_slowdown;
        int m_flash_counter;

        void move();

    public:
        Enemy();
        ~Enemy();

        int eventHandler(const df::Event* p_e) override;

        void setHP(int hp);
        int getHP() const;

        void flash();
};

#endif