//includes background sprite info and potential interactable objects. A 1x1 area on the grid.
#include <string>
#include "Vector.h"

class Room {
    private:
        //based on Hero's currentDirection. Have to check Hero. Is this recurisve? Does Hero also have to check Room for something?
        void setCurrentSprite();
        void setNorthSpriteString(std::string sprite);
        void setEastSpriteString(std::string sprite);
        void setSouthSpriteString(std::string sprite);
        void setWestSpriteString(std::string sprite);

        bool isNorthBlocked;
        bool isEastBlocked;
        bool isSouthBlocked;
        bool isWestBlocked;

        df::Vector gridPosition; //not position on screen, position in map

        std::string northSprite;
        std::string eastSprite;
        std::string southSprite;
        std::string westSprite;

    public:
        Room();
        ~Room();
        int eventHandler(const df::Event *p_e) override;
};