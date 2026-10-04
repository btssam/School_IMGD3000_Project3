//Enemy that floats around and must be clicked to be desroyed
#pragma once

// Engine includes
#include "Object.h"
#include "EventStep.h"

class Enemy : public df::Object {
    private:
        //current hp of enemy
        int m_hp;
        //cooldown for movement
        int m_moveCooldown;
        //counter for movement cooldown
        int m_move_countdown;
        //cooldown for flashing when hit
        int m_flash_slowdown;
        // counter for flashing when hit
        int m_flash_counter;
        //move enemy in a random direction
        void move();

    public:
        //constructor and destructor
        Enemy();
        ~Enemy();
        //event handler for step event
        int eventHandler(const df::Event* p_e) override;
        //set current hp of enemy
        void setHP(int hp);
        //get current hp of enemy
        int getHP() const;
        //flash enemy when hit
        void flash();
};