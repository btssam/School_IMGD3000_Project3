//includes background sprite info and potential interactable objects. A 1x1 area on the grid.
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

        // Optional attributes:
        // std::string m_description;
        // bool m_has_enemy;
        // bool m_visited;
    public:
        Room();
        Room(bool north, bool east, bool south, bool west);
        // bool hasWallNorth() const { return isWallNorth; }
        // bool hasWallEast() const  { return isWallEast; }
        // bool hasWallSouth() const { return isWallSouth; }
        // bool hasWallWest() const  { return isWallWest; }

        //North, East, South, West
        void setWalls(bool north, bool east, bool south, bool west);


        // Setters for wall blockage
        void setIsNorthWall(bool blocked);
        void setIsEastWall(bool blocked);
        void setIsSouthWall(bool blocked);
        void setIsWestWall(bool blocked);
        // Setters for sprite names
        void setNorthSpriteString(std::string sprite);
        void setEastSpriteString(std::string sprite);
        void setSouthSpriteString(std::string sprite);
        void setWestSpriteString(std::string sprite);
        // Position on the map grid
        void setGridPosition(df::Vector pos);
        df::Vector getGridPosition() const;
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
};
