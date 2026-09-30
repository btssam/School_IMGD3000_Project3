#include "Bullet.h"

#include "EventOut.h"
#include "WorldManager.h"

Bullet::Bullet(df::Vector hero_pos){
    setSprite("bullet");
    setType("Bullet");

    //set position based on hero's position
    df:: Vector p(hero_pos.getX() + 3, hero_pos.getY());
    setPosition(p);

    setSpeed(1);

    //ignore collision for hero only
    setSolidness(df::SOFT);
}

int Bullet::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::OUT_EVENT){
        out();
        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT){
        const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
        hit(p_collision_event);
        return 1;
    }
    return 0;
}

void Bullet::out(){
    WM.markForDelete(this);
}

//object 1 = initiater of collision. object2 = thing collided into
void Bullet::hit(const df::EventCollision *p_collision_event){
    if ((p_collision_event->getObject1()->getType() == "Saucer") || (p_collision_event->getObject2()->getType() == "Saucer")){
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
    }
}