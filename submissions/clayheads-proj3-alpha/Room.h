//includes background sprite info and potential interactable objects. A 1x1 area on the grid.
//not an object, basically just a container for the information for a given room
#pragma once

//System includes
#include <string>
//Engine includes
#include "Vector.h"

enum class Direction {
    NORTH = -1,
    EAST = 0,
    SOUTH,
    WEST,
};

class Room {
    private:
        //true if wall is present in the north direction
        bool isWallNorth;
        //true if wall is present in the east direction
        bool isWallEast;
        //true if wall is present in the south direction
        bool isWallSouth;
        //true if wall is present in the west direction
        bool isWallWest;

        //position of the room on the map grid
        df::Vector gridPosition;

        //sprite name for the north direction (could be wall or hallway)
        std::string northSprite;
        //sprite name for the east direction (could be wall or hallway)
        std::string eastSprite;
        //sprite name for the south direction (could be wall or hallway)
        std::string southSprite;
        //sprite name for the west direction (could be wall or hallway)
        std::string westSprite;

        //true if an enemy is present in the room. will do similar pattern for other objects in a room (e.g. keypad, locked doors, fountains)
        bool hasEnemy;
    public:
        //constructor
        Room();

        //set booleans for walls: North, East, South, West
        void setWalls(bool north, bool east, bool south, bool west);

        //set north sprite name
        void setNorthSpriteString(std::string sprite);
        //set east sprite name
        void setEastSpriteString(std::string sprite);
        //set south sprite name
        void setSouthSpriteString(std::string sprite);
        //set west sprite name
        void setWestSpriteString(std::string sprite);
        // Position on the map grid
        void setGridPosition(df::Vector pos);
        // get wall blockage boolean for north direction
        bool getIsNorthWall() const;
        // get wall blockage boolean for east direction
        bool getIsEastWall() const;
        // get wall blockage boolean for south direction
        bool getIsSouthWall() const;
        // get wall blockage boolean for west direction
        bool getIsWestWall() const;
        // get sprite name for north direction
        std::string getNorthSprite() const;
        // get sprite name for east direction
        std::string getEastSprite() const;
        // get sprite name for south direction
        std::string getSouthSprite() const;
        // get sprite name for west direction
        std::string getWestSprite() const;
        //set hasEnemy boolean
        void setHasEnemy(bool enemy);
        //get hasEnemy boolean
        bool getHasEnemy();
};
