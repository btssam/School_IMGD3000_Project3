//A cursor like object that is currently only used when fighting
#pragma once

// Engine includes
#include "Object.h"


class Reticle : public df::Object {
    private:
        //movement & hover helpers
        void handleMouseMove(df::Vector mouse_pos);
        //click routing
        void handleMouseClick(df::Vector click_pos);

        bool checkEnemy(df::Vector click_pos);
        bool checkFountain(df::Vector click_pos);


    public:
        //constructor
        Reticle();

        //draw override
        int draw() override;
        //event handler override
        int eventHandler(const df::Event* p_e) override;
};