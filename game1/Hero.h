//Hero is not actual drawn on screen, as its first person. Just tracks hero info and hanldes hero behaviors

#include "Object.h"
#include "EventKeyboard.h"
#include "Vector.h"
// #include "EventMouse.h"
// #include "Reticle.h"

#include "Room.h"
#include "UI.h"


class Hero : public df::Object {
    private:
        UI* p_ui;
        void kbd(const df::EventKeyboard *p_keyboard_event);
        void move_up();
        void turn_left();
        void turn_right();
        void step();

        // void take_damage(); //lower hp
        // void attack(); //use reticle to attack if facing an enemy

        enum class Direction {
        NORTH = -1,
        EAST = 0,
        SOUTH,
        WEST,
        };


        bool isFacingWall; //disables moving_up
        
        Direction facingDirection;

        //Room currentRoom; #still need to make Room.h/cpp



        int move_slowdown; //delay input for keybaord
        int move_countdown;

        df::Vector gridPosition; //not position on screen, position in map

        // bool isFighting; //true if in a room with an enemy. disable movement and enable attack

        // int fire_slowdown;  //delay input when fighting (maybe not needed)
        // int fire_countdown;

        // void fire(df::Vector target);
        // void mouse(const df::EventMouse *p_mouse_event);

        // Reticle *p_reticle; //probably want a reticle for fighting
    public:
        Hero(UI* p_ui);
        ~Hero();
        int eventHandler(const df::Event *p_e) override;
};