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

        //true if an enemy is present in the room.
        bool hasEnemy;
        //true if a fountain is in the room.
        bool hasFountain;
        //direction of fountain
        Direction fountainWall;
        //true if a clue is in the room
        bool hasClue;
        std::string clueSprite;
        //duection of clue sprite
        Direction clueWall;
        //true if color clue is in the room
        bool hasColorClue;
        //direction of colorclue wall
        Direction colorClueWall;
        //true if a keypad is in the room
        bool hasKeypad;
        //direction of keypad wall
        Direction keypadWall;

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

        //set hasFountain boolean
        void setHasFountain(bool fountain);
        //get hasFountain boolean
        bool getHasFountain();
        //set fountain wall
        void setFountainWall(Direction wall);
        //get fountain wall
        Direction getFountainWall() const;

        //set hasClue boolean
        void setHasClue(bool clue);
        //get hasClue boolean
        bool getHasClue();
        //set clue sprite
        void setClueSprite(std::string sprite);
        //get clue sprite
        std::string getClueSprite() const;
        //set clue wall
        void setClueWall(Direction wall);
        //get clue wall
        Direction getClueWall() const;

        //set color clue boolean
        void setHasColorClue(bool clue);
        //get color clue boolean
        bool getHasColorClue();
        //set color clue wall
        void setColorClueWall(Direction wall);
        //get color clue wall
        Direction getColorClueWall() const;


        void setHasKeypad(bool keypad);
        bool getHasKeypad() const;
        void setKeypadWall(Direction wall);
        Direction getKeypadWall() const;
};
