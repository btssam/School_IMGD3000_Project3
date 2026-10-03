#ifndef RETICLE_H
#define RETICLE_H

#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {
    public:
        Reticle();

        int draw() override;
        int eventHandler(const df::Event* p_e) override;
};

#endif