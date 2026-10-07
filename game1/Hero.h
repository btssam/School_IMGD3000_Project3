//Hero is not actual drawn on screen, as its first person.
//tracks hero info and hanldes hero behaviors
#pragma once

//engine includes
#include "Object.h"
#include "EventKeyboard.h"
#include "Vector.h"
//game includes
#include "Room.h"
#include "UI.h"
#include "Map.h"

//forward declaration
class Enemy;

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
        // Combat handling
        void checkCombat();
        //spawn an enemy in the room and start combat
        void spawnEnemy(Room* p_room);
        //configure the boss enemy with special attributes
        void configureBoss(Enemy* p_enemy);

        // Room object spawning
        void checkRoomObjects();
        //spawn a fountain if present in room
        void spawnFountain(Room* p_room);
        //spawn a clue if present in room
        void spawnClue(Room* p_room);
        //spawn a color clue if present in room
        void spawnColorClue(Room* p_room);
        //spawn a keypad if present in room
        void spawnKeypad(Room* p_room);

        //update visibilty of fountain
        void updateFountains();
        //update visibility of clue
        void updateClues();
        //update visibility of color clue
        void updateColorClues();
        //update visibility of keypad
        void updateKeypads();

    public:
        //constructor
        Hero(UI* p_ui, Map* p_map);
        //destructor
        ~Hero();
        //event handler
        int eventHandler(const df::Event *p_e) override;
        //check if fighting
        bool getIsFighting() const;
};