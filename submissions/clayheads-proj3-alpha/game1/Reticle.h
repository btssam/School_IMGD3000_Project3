//A cursor like object that is currently only used when fighting
#pragma once

// Engine includes
#include "Object.h"

class Reticle : public df::Object {
    public:
        //constructor
        Reticle();

        //draw override
        int draw() override;
        //event handler override
        int eventHandler(const df::Event* p_e) override;
};