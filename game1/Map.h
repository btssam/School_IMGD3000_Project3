//series of Rooms, in x-y grid
//also handles the visual generation of the current room (the sprite)
#pragma once

// Engine includes
#include "Object.h"
// Game includes
#include "Room.h"

const int MAX_MAP_WIDTH = 32;
const int MAX_MAP_HEIGHT = 32;
const int MAP_WIDTH = MAX_MAP_WIDTH;
const int MAP_HEIGHT = MAX_MAP_HEIGHT;

class Map: public df::Object {
    private:
        //map width
        int map_width;
        //map height
        int map_height;
        //2D array of rooms
        Room grid[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
    
    public:
        //Map Construction
        Map();
        //Map Destructor
        ~Map();
        //get a specific room pointer at a particular grid position
        Room* getRoom(int x, int y);
        //update the actual visual sprite representation, based on hero's grid position and facing direction
        void updateView(df::Vector heroPos, Direction heroDir);
        //generaate map (sets boolean wall values and sprites for each room) based on minimap sprite
        void generateMapFromSprite(std::string spriteName);
        //get map width
        int getMapWidth() const;
        //get mapheight
        int getMapHeight() const;

};