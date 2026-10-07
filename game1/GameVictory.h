// Game Victory screen and handles behaviors related to winning the game
#pragma once

// Engine includes
#include "ViewObject.h"
#include "Animation.h"

class GameVictory : public df::ViewObject{
    private:
        //how long the GameVictory screen should stay on screen before deleting itself
        int time_to_live;
        //step event each frame (for countdown)
        void step();

        //animation layers for multi-colored clay pool
        df::Animation m_base_anim;
        df::Animation m_clay_anim;
        df::Animation m_x_anim;
        df::Animation m_sparkles_anim;

    public:
        //constructor
        GameVictory();
        //destructor. removes all objects from the game world
        ~GameVictory();
        //event handler
        int eventHandler(const df::Event *p_e) override;
        //draw override
        int draw() override;
};
