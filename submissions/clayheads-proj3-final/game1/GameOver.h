// Game Over screen and handles behaviors related to ending the games
#pragma once

// Engine includes
#include "ViewObject.h"

class GameOver : public df::ViewObject{
    private:
        //how long the GameOver screen should stay on screen before deleting itself
        int time_to_live;
        //step event each frame (for countdown)
        void step();
    
    public:
        //constructor
        GameOver();
        //destructor. removes all objects from the game world
        ~GameOver();
        //event handler
        int eventHandler(const df::Event *p_e) override;
        //draw override
        int draw() override;
};