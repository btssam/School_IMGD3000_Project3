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
        //countdown timer for spawn pause (lets player get ready)
        int m_spawn_countdown;
        //cooldown for flashing when hit
        int m_flash_slowdown;
        // counter for flashing when hit
        int m_flash_counter;
        //name, for log references
        std::string m_name;
        //default sprite string
        std::string m_sprite_normal;
        //hit sprite string
        std::string m_sprite_hit;
        //string sound damage
        std::string m_sound_damage;
        //string sound death
        std::string m_sound_death;
        //step displacement x
        int m_step_x;
        //step displacement y
        int m_step_y;
        //roaming boundary: min x
        int m_min_x;
        //roaming boundary: max x
        int m_max_x;
        //roaming boundary: min y
        int m_min_y;
        //roaming boundary: max y
        int m_max_y;

        //move enemy in a random direction
        void move();

    public:
        //constructor
        Enemy();
        //destrcutor
        ~Enemy();
        //event handler for step event
        int eventHandler(const df::Event* p_e) override;
        //set current hp of enemy
        void setHP(int hp);
        //get current hp of enemy
        int getHP() const;
        //flash enemy when hit
        void flash();
        //set name of enemy
        void setName(std::string name);
        //set sprite for normal state
        void setSpriteNormal(std::string sprite);
        //set sprite for hit state
        void setSpriteHit(std::string sprite);
        //set sound string for damage
        void setSoundDamage(std::string sound);
        //set sound string for death
        void setSoundDeath(std::string sound);
        //set movement speed
        void setMoveCooldown(int cooldown);
        //get name of enemy
        std::string getName() const;
        //get sprite for normal state
        std::string getSpriteNormal() const;
        //get sprite for hit state
        std::string getSpriteHit() const;
        //get sound string for damage
        std::string getSoundDamage() const;
        //get sound string for death
        std::string getSoundDeath() const;
        //get movement speed
        int getMoveCooldown() const;
        //set step displacement
        void setStepSize(int step_x, int step_y);
        //set roaming boundaries
        void setBounds(int min_x, int max_x, int min_y, int max_y);
        //get spawn delay countdown
        int getSpawnCountdown() const;
        //set spawn delay countdown
        void setSpawnCountdown(int countdown);
};