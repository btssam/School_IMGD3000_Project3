#include "Saucer.h"
#include "Explosion.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventSlow.h"

#include "EventOut.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventStep.h"

#include <stdlib.h>


Saucer::Saucer(){
    setSprite("saucer");

    //set object type for later detection
    setType("Saucer");

    //set speed in horizontal direction
    setVelocity(df::Vector(-0.25,0)); //1 space to the left every 4 frames

    registerInterest(NUKE_EVENT);
    registerInterest(SLOW_EVENT);
    registerInterest(df::STEP_EVENT);

    slow_cooldown = 0;

    moveToStart();
}

Saucer::~Saucer(){
    //send view event with points to interested viewObjects
    df::EventView ev(POINTS_STRING, 10, true);
    WM.onEvent(&ev);
}

int Saucer::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::OUT_EVENT){
        out();
        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT){
        const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
        hit(p_collision_event);
        return 1;
    }
    if (p_e->getType() == NUKE_EVENT){
        new Saucer;
        Explosion *p_explosion = new Explosion;
        p_explosion->setPosition(this->getPosition());
        WM.markForDelete(this);
        return 1;
    }
    //temporarily lower speed and turn blue
    if (p_e->getType() == SLOW_EVENT){
        slow_cooldown = 200;
        setVelocity(df::Vector(-0.08,0));
        setSprite("saucer-blue");
        return 1;
    }
    if (p_e->getType() == df::STEP_EVENT){
        step();
        return 1;
    }


    return 0;
}

void Saucer::out(){
    //if it did not leave via the left-most edge e.g. by spawning off the right side
    if (getPosition().getX() >= 0)
        return;
    moveToStart();

    new Saucer;
}

void Saucer::moveToStart(){
    df::Vector temp_pos;
    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();

    //x is off right side of window
    temp_pos.setX(world_horiz + rand() % (int) world_horiz + 3.0f);

    //y is in vertical range
    temp_pos.setY(rand() % (int) (world_vert-5) + 4.0f);

    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (collision_list.getCount() != 0){
        temp_pos.setX(temp_pos.getX()+1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision *p_c){
    //ignore collision if Saucer hits Saucer
    if ((p_c->getObject1()->getType() == "Saucer") && (p_c->getObject2()->getType() == "Saucer"))
        return;
    
    if ((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet")){
        Explosion *p_explosion = new Explosion;
        p_explosion->setPosition(this->getPosition());

        //spawn new saucer when destroyed to keep game flow
        new Saucer;
    }

    if ((p_c->getObject1()->getType() == "Hero") || (p_c->getObject2()->getType() == "Hero")){
        WM.markForDelete(p_c->getObject1());
        WM.markForDelete(p_c->getObject2());
    }
}

void Saucer::step(){
    if (slow_cooldown <= 0)
        return;
    slow_cooldown--;

    //restore normal saucer speed/sprite
    if (slow_cooldown == 0){
        setVelocity(df::Vector(-0.25,0));
        setSprite("saucer");
    }
}