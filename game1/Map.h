//series of Rooms, in x-y grid
#pragma once

#include "Room.h"
#include "Object.h"

const int MAP_WIDTH = 3;
const int MAP_HEIGHT = 3;

class Map: public df::Object {
    private:
        Room grid[MAP_WIDTH][MAP_HEIGHT];
    
    public:
        Map();
        ~Map();
        Room* getRoom(int x, int y);
        void updateView(df::Vector heroPos, Direction heroDir);
};