//includes background sprite info and potential interactable objects. A 1x1 area on the grid.
//not an object, basically just a container for the information for a given room
#pragma once


#include <string>
#include "Vector.h"

enum class Direction {
    NORTH = -1,
    EAST = 0,
    SOUTH,
    WEST,
};

class Room {
    private:
        bool isWallNorth;
        bool isWallEast;
        bool isWallSouth;
        bool isWallWest;

        df::Vector gridPosition;

        std::string northSprite;
        std::string eastSprite;
        std::string southSprite;
        std::string westSprite;

        bool hasEnemy;

        // Optional attributes:
        // std::string m_description;
        // bool m_has_enemy;
        // bool m_visited;
    public:
        Room();

        //North, East, South, West
        void setWalls(bool north, bool east, bool south, bool west);


        // Setters for sprite names
        void setNorthSpriteString(std::string sprite);
        void setEastSpriteString(std::string sprite);
        void setSouthSpriteString(std::string sprite);
        void setWestSpriteString(std::string sprite);
        // Position on the map grid
        void setGridPosition(df::Vector pos);
        // Getters for wall blockage
        bool getIsNorthWall() const;
        bool getIsEastWall() const;
        bool getIsSouthWall() const;
        bool getIsWestWall() const;
        // Getters for sprite names
        std::string getNorthSprite() const;
        std::string getEastSprite() const;
        std::string getSouthSprite() const;
        std::string getWestSprite() const;
        //getter and setter for hasEnemy
        void setHasEnemy(bool enemy);
        bool getHasEnemy();
};
