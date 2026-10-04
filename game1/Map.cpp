//System includes
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Engine includes
#include "LogManager.h"

//Game includes
#include "Map.h"

Map::Map(){
    setType("Map");
    //position on screen: center of the 80x18 area above UI
    setPosition(df::Vector(40, 8.5));

    map_width = 0;
    map_height = 0;

    //create 2d array of rooms
    for (int x = 0; x < MAX_MAP_WIDTH; x++){
        for (int y = 0; y < MAX_MAP_HEIGHT; y++){
            grid[x][y] = Room();
            grid[x][y].setGridPosition(df::Vector(x, y));
        }
    }

    //generate map based on sprite
    generateMapFromSprite("sprites/map_1_3x3.txt");

    //configure room sprite and walls manually
    //[0][0] is top left. [0][1] is one down from [0][0], etc. [1][0] is one right from [0][0], etc.
    //make sure hallways are connected via the same sprite (e.g if south of [0][0] is hallway-1, north of [0][1] is also hallway-1). so that if u turn around, it's the same hallway you saw on the way there. walls are less important
    //walls and hallway sprites are from 1 to 4
    //the order might seem kind of weird, but I have to keep in mind adjacent hallways, so Im just kind of tracing through the map in a way that makes sense to me.
    //for now, Im just incrementing the wall/hallway numbers whenever I want a new one

    /*
    //starting position
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

    //ending position
    grid[2][0].setWalls(true, true, true, false);
    grid[2][0].setNorthSpriteString("wall-2");
    grid[2][0].setEastSpriteString("wall-3");
    grid[2][0].setSouthSpriteString("wall-4");
    grid[2][0].setWestSpriteString("hallway-4");
    */

    //Put specific objects/enemies interactables here
    grid[2][0].setHasEnemy(true);
}

Map::~Map(){
}

Room* Map::getRoom(int x, int y){
    if (x < 0 || x >= map_width || y < 0 || y >= map_height){
        return nullptr;
    }
    return &grid[x][y];
}

int Map::getMapWidth() const {
    return map_width;
}

int Map::getMapHeight() const {
    return map_height;
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

void Map::generateMapFromSprite(std::string spriteName) {
    std::string filePath = spriteName;
    if (filePath.find("sprites/") == std::string::npos) {
        filePath = "sprites/" + filePath;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        df::LogManager* log_manager = &df::LogManager::getInstance();
        log_manager->writeLog("Map::generateMapFromSprite: Could not open sprite file '%s'", filePath.c_str());
        return;
    }

    std::string line;
    int spr_w = 0;
    int spr_h = 0;
    bool in_header = false;
    bool in_body = false;
    std::vector<std::string> body_lines;

    while (std::getline(file, line)) {
        // Strip trailing carriage return '\r' for cross-platform compatibility
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line == "<HEADER>") {
            in_header = true;
            continue;
        }
        if (line == "</HEADER>") {
            in_header = false;
            continue;
        }
        if (line == "<BODY>") {
            in_body = true;
            continue;
        }
        if (line == "</BODY>") {
            in_body = false;
            break;
        }

        if (in_header) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;
            if (token == "width") {
                iss >> spr_w;
            } else if (token == "height") {
                iss >> spr_h;
            }
        } else if (in_body) {
            if (line == "end") {
                break;
            }
            body_lines.push_back(line);
        }
    }
    file.close();

    //each room is 3x1 characters in the minimap
    map_width = (spr_w - 1) / 3;
    map_height = spr_h - 1;

    if (map_width > MAX_MAP_WIDTH || map_height > MAX_MAP_HEIGHT) {
        df::LogManager* log_manager = &df::LogManager::getInstance();
        log_manager->writeLog("Map::generateMapFromSprite: Map dimensions (%d x %d) exceed MAX (%d x %d)",
            map_width, map_height, MAX_MAP_WIDTH, MAX_MAP_HEIGHT);
        return;
    }

    // Initialize all rooms for the detected map size
    for (int x = 0; x < map_width; x++) {
        for (int y = 0; y < map_height; y++) {
            grid[x][y] = Room();
            grid[x][y].setGridPosition(df::Vector(x, y));
        }
    }

    // body_lines[0] is the top border line (e.g. " ________ ")
    // body_lines[1 + y] corresponds to row y of rooms
    if (static_cast<int>(body_lines.size()) < 1 + map_height) {
        df::LogManager* log_manager = &df::LogManager::getInstance();
        log_manager->writeLog("Map::generateMapFromSprite: Insufficient lines in body (%zu found, expected %d)",
            body_lines.size(), 1 + map_height);
        return;
    }

    // Determine walls for each room
    for (int y = 0; y < map_height; y++) {
        std::string row_str = body_lines[1 + y];

        for (int x = 0; x < map_width; x++) {
            int char_start = 1 + x * 3;

            // South wall: first two characters are "__"
            bool is_wall_south = false;
            if (char_start + 1 < static_cast<int>(row_str.size())) {
                if (row_str[char_start] == '_' && row_str[char_start + 1] == '_') {
                    is_wall_south = true;
                }
            }

            // East wall: third character is '|'
            bool is_wall_east = false;
            if (char_start + 2 < static_cast<int>(row_str.size())) {
                if (row_str[char_start + 2] == '|') {
                    is_wall_east = true;
                }
            }

            // North wall: row 0 has north wall; otherwise matches room above's south wall
            bool is_wall_north = false;
            if (y == 0) {
                is_wall_north = true;
            } else {
                Room* p_above = &grid[x][y - 1];
                is_wall_north = p_above->getIsSouthWall();
            }

            // West wall: col 0 has west wall; otherwise matches room to the left's east wall
            bool is_wall_west = false;
            if (x == 0) {
                is_wall_west = true;
            } else {
                Room* p_left = &grid[x - 1][y];
                is_wall_west = p_left->getIsEastWall();
            }

            Room* p_room = &grid[x][y];
            p_room->setWalls(is_wall_north, is_wall_east, is_wall_south, is_wall_west);
        }
    }

    // Assign sprites for walls and hallways. Uses counters to cycle through wall and hallway sprite numbers for variety. Assures adjacent/attached hallways have the same sprite as well.
    int wall_counter = 1;
    int hallway_counter = 1;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            Room* p_room = &grid[x][y];

            // 1. NORTH
            if (p_room->getIsNorthWall()) {
                p_room->setNorthSpriteString("wall-" + std::to_string(wall_counter));
                wall_counter = (wall_counter % 4) + 1;
            } else {
                // Inherit South sprite from room above
                Room* p_above = &grid[x][y - 1];
                p_room->setNorthSpriteString(p_above->getSouthSprite());
            }

            // 2. WEST
            if (p_room->getIsWestWall()) {
                p_room->setWestSpriteString("wall-" + std::to_string(wall_counter));
                wall_counter = (wall_counter % 4) + 1;
            } else {
                // Inherit East sprite from room to the left
                Room* p_left = &grid[x - 1][y];
                p_room->setWestSpriteString(p_left->getEastSprite());
            }

            // 3. SOUTH
            if (p_room->getIsSouthWall()) {
                p_room->setSouthSpriteString("wall-" + std::to_string(wall_counter));
                wall_counter = (wall_counter % 4) + 1;
            } else {
                // New hallway connection leading South
                p_room->setSouthSpriteString("hallway-" + std::to_string(hallway_counter));
                hallway_counter = (hallway_counter % 4) + 1;
            }

            // 4. EAST
            if (p_room->getIsEastWall()) {
                p_room->setEastSpriteString("wall-" + std::to_string(wall_counter));
                wall_counter = (wall_counter % 4) + 1;
            } else {
                // New hallway connection leading East
                p_room->setEastSpriteString("hallway-" + std::to_string(hallway_counter));
                hallway_counter = (hallway_counter % 4) + 1;
            }
        }
    }
}