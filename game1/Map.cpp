#include "Map.h"

Map::Map(){
    setType("Map");
    //position on screen: center of the 80x18 area above UI
    setPosition(df::Vector(40, 8.5));

    //create room
    for (int x = 0; x< MAP_WIDTH; x++){
        for (int y = 0; y< MAP_HEIGHT; y++){
            grid[x][y] = Room();
            grid[x][y].setGridPosition(df::Vector(x, y));
        }
    }

    //configure room sprite and walls manually
    //[0][0] is top left. [0][1] is one down from [0][0], etc. [1][0] is one right from [0][0], etc.
    //make sure hallways are connected via the same sprite (e.g if south of [0][0] is hallway-1, north of [0][1] is also hallway-1). so that if u turn around, its the same hallway you saw on the way there. walls are less important
    //walls and hallway sprites are from 1 to 4
    //the order might seem kind of weird, but I have to keep in mind adjacent hallways, so Im just kind of tracing through the map in a way that makes sense to me.
    //for now, Im just incrementing the wall/hallway numbers whenever I want a new one

    //start
    grid[0][0].setWalls(true, true, false, true);
    grid[0][0].setNorthSpriteString("wall-1");
    grid[0][0].setEastSpriteString("wall-2");
    grid[0][0].setSouthSpriteString("hallway-1");
    grid[0][0].setWestSpriteString("wall-3");

    grid[0][1].setWalls(false, true, false, true);
    grid[0][1].setNorthSpriteString("hallway-1");
    grid[0][1].setEastSpriteString("wall-4");
    grid[0][1].setSouthSpriteString("hallway-2");
    grid[0][1].setWestSpriteString("wall-1");

    grid[0][2].setWalls(false, false, true, true);
    grid[0][2].setNorthSpriteString("hallway-2");
    grid[0][2].setEastSpriteString("hallway-3");
    grid[0][2].setSouthSpriteString("wall-2");
    grid[0][2].setWestSpriteString("wall-4");

    grid[1][2].setWalls(true, false, true, false);
    grid[1][2].setNorthSpriteString("wall-3");
    grid[1][2].setEastSpriteString("hallway-4");
    grid[1][2].setSouthSpriteString("wall-1");
    grid[1][2].setWestSpriteString("hallway-3");

    grid[2][2].setWalls(false, true, true, false);
    grid[2][2].setNorthSpriteString("hallway-1");
    grid[2][2].setEastSpriteString("wall-2");
    grid[2][2].setSouthSpriteString("wall-3");
    grid[2][2].setWestSpriteString("hallway-4");

    grid[2][1].setWalls(true, true, false, false);
    grid[2][1].setNorthSpriteString("wall-4");
    grid[2][1].setEastSpriteString("wall-1");
    grid[2][1].setSouthSpriteString("hallway-1");
    grid[2][1].setWestSpriteString("hallway-2");

    grid[1][1].setWalls(false, false, true, true);
    grid[1][1].setNorthSpriteString("hallway-3");
    grid[1][1].setEastSpriteString("hallway-2");
    grid[1][1].setSouthSpriteString("wall-2");
    grid[1][1].setWestSpriteString("wall-3");

    grid[1][0].setWalls(true, false, false, true);
    grid[1][0].setNorthSpriteString("wall-4");
    grid[1][0].setEastSpriteString("hallway-4");
    grid[1][0].setSouthSpriteString("hallway-3");
    grid[1][0].setWestSpriteString("wall-1");

    //end
    grid[2][0].setWalls(true, true, true, false);
    grid[2][0].setNorthSpriteString("wall-2");
    grid[2][0].setEastSpriteString("wall-3");
    grid[2][0].setSouthSpriteString("wall-4");
    grid[2][0].setWestSpriteString("hallway-4");

    //Put specific objects/enemies interactables here
    grid[2][0].setHasEnemy(true);
}

Map::~Map(){
}

Room* Map::getRoom(int x, int y){
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT){
        return nullptr;
    }
    return &grid[x][y];
}

void Map::updateView(df::Vector heroPos, Direction heroDir){
    Room* p_room = getRoom(heroPos.getX(), heroPos.getY());
    if (p_room == nullptr) return;

    std::string spriteToDraw = "";
    switch (heroDir) {
        case Direction::NORTH:
            spriteToDraw = p_room->getNorthSprite();
            break;
        case Direction::EAST:
            spriteToDraw = p_room->getEastSprite();
            break;
        case Direction::SOUTH:
            spriteToDraw = p_room->getSouthSprite();
            break;
        case Direction::WEST:
            spriteToDraw = p_room->getWestSprite();
            break;
    }

    setSprite(spriteToDraw);
}