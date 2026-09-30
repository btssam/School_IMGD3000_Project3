#include "Reticle.h"

#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"

Reticle::Reticle(){
    setType("Reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE); //z layer - determines object drawing order
    registerInterest(df::MSE_EVENT);


    //set starting location in the middle
    int world_horiz = (int) WM.getBoundary().getHorizontal();
    int world_vert = (int) WM.getBoundary().getVertical();
    df::Vector p(world_horiz/2, world_vert/2);
    setPosition(p);
}

int Reticle::draw(void){
    return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}

int Reticle::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df:: MSE_EVENT){
        const df::EventMouse *p_mouse_event = dynamic_cast < const df::EventMouse *> (p_e);

        if (p_mouse_event->getMouseAction() == df::MOVED){
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }

    return 0;
}