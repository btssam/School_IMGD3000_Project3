#pragma once
//handles all the UI elements, including the health bar, map, and log messages. not directly interactable, just drawn

//System includes
#include <string>
#include <vector>

//Engine includes
#include "Object.h"
#include "Vector.h"

class UI : public df::Object {
    private:
        //heros current hp
        int m_hp;
        //heros max hp
        int m_max_hp;
        //log messages to display on the screen
        std::vector<std::string> m_log;
        //position of the hero in the grid
        df::Vector m_hero_pos;
        //sprite label for the minimap
        std::string m_map_sprite_label;

    public:
        //constructor
        UI();
        //draw override
        int draw() override;
        //event handler override
        int eventHandler(const df::Event* p_e) override;
        //set current hp of hero
        void setHP(int hp);
        //get current hp of hero
        int getHP() const;
        //add a log message to the UI
        void addLogMessage(std::string message);
        //set hero position on the map
        void setHeroPosition(df:: Vector pos);
        //set the sprite label for the minimap
        void setMapSprite(std::string sprite_label);
};