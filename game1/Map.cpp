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
    setPosition(df::Vector(40.5, 8.5));
    setAltitude(0);

    map_width = 0;
    map_height = 0;

    //create 2d array of rooms
    for (int x = 0; x < MAX_MAP_WIDTH; x++){
        for (int y = 0; y < MAX_MAP_HEIGHT; y++){
            grid[x][y] = Room();
            grid[x][y].setGridPosition(df::Vector(x, y));
        }
    }

    generateMapFromSprite("sprites/map_1_8x16.txt");

    //Put specific objects/enemies interactables here
    // Rooms with enemies
    grid[8][0].setHasEnemy(true);
    grid[3][2].setHasEnemy(true);
    grid[9][3].setHasEnemy(true);
    grid[13][3].setHasEnemy(true);
    grid[0][2].setHasEnemy(true);
    // Rooms with fountains
    grid[3][1].setHasFountain(true);
    grid[3][1].setFountainWall(Direction::NORTH);
    grid[1][3].setHasFountain(true);
    grid[1][3].setFountainWall(Direction::NORTH);
    grid[8][2].setHasFountain(true);
    grid[8][2].setFountainWall(Direction::WEST);
    grid[11][1].setHasFountain(true);
    grid[11][1].setFountainWall(Direction::SOUTH);
    // Rooms with clues
    grid[0][1].setHasClue(true);
    grid[0][1].setClueSprite("clue-2");
    grid[0][1].setClueWall(Direction::NORTH);
    grid[5][0].setHasClue(true);
    grid[5][0].setClueSprite("clue-6");
    grid[5][0].setClueWall(Direction::NORTH);
    grid[9][1].setHasClue(true);
    grid[9][1].setClueSprite("clue-9");
    grid[9][1].setClueWall(Direction::NORTH);
    grid[13][1].setHasClue(true);
    grid[13][1].setClueSprite("clue-7");
    grid[13][1].setClueWall(Direction::WEST);
    // Room with color clue
    grid[11][3].setHasColorClue(true);
    grid[11][3].setColorClueWall(Direction::EAST);

    //Room with keypad
    grid[14][4].setHasKeypad(true);
    grid[14][4].setKeypadWall(Direction::EAST);
    //override map generation at this position, to set a wall here until keypad is solved (wall currently doesnt show up on map - could add if I wanted to, but keeps it mysterious I guess)
    grid[14][4].setWalls(false, true, true, false);
    grid[14][4].setEastSpriteString("wall-1");
    grid[15][4].setHasEnemy(true);
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
                // New hallway connection leading South (connecting grid[x][y] and grid[x][y+1]).
                // To avoid visual confusion when turning in a room or moving forward down a corridor,
                // collect all hallway sprites already assigned to adjacent exits touching this passage.
                std::vector<std::string> avoid;
                if (!p_room->getIsNorthWall()) avoid.push_back(p_room->getNorthSprite());
                if (!p_room->getIsWestWall())  avoid.push_back(p_room->getWestSprite());
                // Avoid the West exit of the room below us if it was already assigned
                if (y + 1 < map_height && x > 0 && !grid[x][y + 1].getIsWestWall()) {
                    avoid.push_back(grid[x - 1][y + 1].getEastSprite());
                }

                // Pick the next candidate number (1 to 4) cycling from hallway_counter that has no conflicts
                int chosen = hallway_counter;
                for (int i = 0; i < 4; i++) {
                    int candidate = ((hallway_counter - 1 + i) % 4) + 1;
                    std::string cand_str = "hallway-" + std::to_string(candidate);
                    bool conflict = false;
                    for (size_t k = 0; k < avoid.size(); k++) {
                        if (avoid[k] == cand_str) {
                            conflict = true;
                            break;
                        }
                    }
                    if (!conflict) {
                        chosen = candidate;
                        break;
                    }
                }

                p_room->setSouthSpriteString("hallway-" + std::to_string(chosen));
                hallway_counter = (chosen % 4) + 1;
            }

            // 4. EAST
            if (p_room->getIsEastWall()) {
                p_room->setEastSpriteString("wall-" + std::to_string(wall_counter));
                wall_counter = (wall_counter % 4) + 1;
            } else {
                // New hallway connection leading East (connecting grid[x][y] and grid[x+1][y]).
                // Avoid hallway sprites from any open exits touching this passage:
                // - Current room's North, West, and South exits
                // - Destination room's North exit (from the room above it)
                std::vector<std::string> avoid;
                if (!p_room->getIsNorthWall()) avoid.push_back(p_room->getNorthSprite());
                if (!p_room->getIsWestWall())  avoid.push_back(p_room->getWestSprite());
                if (!p_room->getIsSouthWall()) avoid.push_back(p_room->getSouthSprite());
                // Avoid the North exit of the room to our right if it was already assigned
                if (x + 1 < map_width && y > 0 && !grid[x + 1][y].getIsNorthWall()) {
                    avoid.push_back(grid[x + 1][y - 1].getSouthSprite());
                }

                // Pick the next candidate number (1 to 4) cycling from hallway_counter that has no conflicts
                int chosen = hallway_counter;
                for (int i = 0; i < 4; i++) {
                    int candidate = ((hallway_counter - 1 + i) % 4) + 1;
                    std::string cand_str = "hallway-" + std::to_string(candidate);
                    bool conflict = false;
                    for (size_t k = 0; k < avoid.size(); k++) {
                        if (avoid[k] == cand_str) {
                            conflict = true;
                            break;
                        }
                    }
                    if (!conflict) {
                        chosen = candidate;
                        break;
                    }
                }

                p_room->setEastSpriteString("hallway-" + std::to_string(chosen));
                hallway_counter = (chosen % 4) + 1;
            }
        }
    }
}