#include <string>
#include "Event.h"

const std::string SLOW_EVENT = "slow";

class EventSlow : public df::Event {
    public:
        EventSlow();
};