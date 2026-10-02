//series of Rooms, in x-y grid
//also handles the visual generation of the current room (the sprite)
#pragma once

#include "Room.h"
#include "Object.h"

const int MAP_WIDTH = 3;
const int MAP_HEIGHT = 3;

class Map: public df::Object {
    private:
        Room grid[MAP_WIDTH][MAP_HEIGHT];
    
    public:
        //Map Construction
        Map();
        //Map Destructor
        ~Map();
        //get a specific room pointer at a particular grid position
        Room* getRoom(int x, int y);
        //update the actual visual sprite representation, based on hero's grid position and facing direction
        void updateView(df::Vector heroPos, Direction heroDir);
};