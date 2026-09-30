#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {

    private:
        int slow_cooldown;
    
    public:
        Saucer();
        ~Saucer();
        int eventHandler(const df::Event *p_e) override;
        void out();
        void moveToStart();
        void hit(const df::EventCollision *p_c);
        void step();

};