//Hero is not actual drawn on screen, as its first person.
//Just tracks hero info and hanldes hero behaviors
#pragma once

// Engine includes
#include "Object.h"
#include "EventKeyboard.h"
#include "Vector.h"
// Game includes
#include "Room.h"
#include "UI.h"
#include "Map.h"

class Hero : public df::Object {
    private:
        //switch statement for keyboard input
        void kbd(const df::EventKeyboard *p_keyboard_event);
        //move character forward in the direction they are facing
        void move_up();
        //change direction left
        void turn_left();
        //change direction right
        void turn_right();
        //step event each frame (for cooldowns, etc.)
        void step();
        //lowers hp and handles related functinality
        void take_damage(int amount);

        //pointer to UI
        UI* p_ui;
        //disables moving up
        bool isFacingWall; //disables moving_up
        //what direction character is facing
        Direction facingDirection;
        //delay input for keyboard
        int move_slowdown;
        //counter for input delay
        int move_countdown;
        //not position on screen, position in map
        df::Vector gridPosition;
        //pointer to map;
        Map* p_map;
        //counter for taking damage perioidically during a fight
        int take_damage_slowdown;
        //counter for taking damage delay;
        int take_damage_countdown;

        //true if in a room with an enemy. disable movement and enable attack
        bool isFighting;
        //
        void checkCombat();
        //
        void updateFountains();
        //
        void updateClues();
        //
        void updateColorClues();
        //
        void updateKeypads();

    public:
        Hero(UI* p_ui, Map* p_map);
        ~Hero();
        int eventHandler(const df::Event *p_e) override;

        bool getIsFighting() const;
};