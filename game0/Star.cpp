#include "Star.h"

#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"

#include <stdlib.h>

Star::Star(){
    setType("Star");
    setSolidness(df::SPECTRAL);
    //random speed for parallax effect
    setVelocity(df::Vector((float) -1.0 /(rand()%10+1), 0));
    setAltitude(0);
    //random starting position
    df::Vector p((float) (rand()%(int)WM.getBoundary().getHorizontal()), (float) (rand()%(int)WM.getBoundary().getVertical()));
    setPosition(p);
}

int Star::draw(){
    return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

int Star::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::OUT_EVENT){
        out();
        return 1;
    }
    return 0;
}

void Star::out(){
    df::Vector p(
    (float) WM.getBoundary().getHorizontal() + rand()%20,
    (float) (rand()%(int)WM.getBoundary().getVertical()));
    setPosition(p);
    setVelocity(df::Vector(-1.0/(rand()%10+1), 0));
}