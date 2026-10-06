//System includes
#include <string>
//Engine includes
#include "DisplayManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
//Game includes
#include "UI.h"

UI::UI() {
    setType("UI");

    m_max_hp = 100;
    m_hp = m_max_hp;
    m_log.clear();

    int result = setSprite("ui");

    if (result != 0) {
        LM.writeLog("UI: setSprite FAILED");
    }
    else {
        LM.writeLog("UI: setSprite SUCCESS");
    }

    setPosition(df::Vector(40.5, 21.5));

    m_hero_pos = df::Vector(0, 0);
    // m_map_sprite_label = "map-3x3";
    // m_map_sprite_label = "map-8x5";
    m_map_sprite_label = "map-8x16";

    UI::addLogMessage("Find the CLAY POOL!");
}

int UI::draw() {
    int result = df::Object::draw();

    // HP
    DM.drawString(
        df::Vector(4.5, 20),
        std::to_string(m_hp),
        df::CENTER_JUSTIFIED,
        df::RED
    );
    DM.drawString(
        df::Vector(4.5, 21.5),
        "---",
        df::CENTER_JUSTIFIED,
        df::RED
    );
    DM.drawString(
        df::Vector(4.5, 23),
        std::to_string(m_max_hp),
        df::CENTER_JUSTIFIED,
        df::RED
    );

    // Log
    for (int i = 0; i < static_cast<int>(m_log.size()) && i < 6; i++) {
        DM.drawString(
            df::Vector(9.5, 19 + i),
            m_log[i],
            df::LEFT_JUSTIFIED,
            df::WHITE
        );
    }

    //minimap
    df::Sprite* p_map_spr = RM.getSprite(m_map_sprite_label);
    if (p_map_spr != nullptr){
        df::Vector minimap_center(54.5, 21.25);

        //draw the base minimap sprite
        p_map_spr->draw(0, minimap_center, ' ');

        //compute top-left corner of sprite in screen char coordinates (allow for different size maps)
        int spr_w = p_map_spr->getWidth();
        int spr_h = p_map_spr->getHeight();

        float top_left_x = minimap_center.getX() - ((spr_w-1) / 2.0f);
        float top_left_y = minimap_center.getY() - ((spr_h-1) / 2.0f);

        //compute screen coordinates for current room
        float cell_space_x = top_left_x + 1.0f + (m_hero_pos.getX() * 3.0f);
        float cell_space_y = top_left_y + 1.0f + m_hero_pos.getY();


        //convert ascii char coordinates to sfml window pixels
        df::Vector pixel_pos = df::spacesToPixels(df::Vector(cell_space_x, cell_space_y));
        
        //create sfml rectangle to represent character on map
        sf::RectangleShape highlight(sf::Vector2f(df::charWidth() * 2.0f, df::charHeight()));

        highlight.setFillColor(sf::Color(0, 255, 0, 80));
        highlight.setPosition(sf::Vector2f(pixel_pos.getX(), pixel_pos.getY()));

        //draw direction onto SFML render window
        sf::RenderWindow* p_window = DM.getWindow();
        if (p_window != nullptr) {
            p_window->draw(highlight);
        }

    }

    return result;
}

void UI::setHP(int hp) {
    m_hp = hp;
}

int UI::getHP() const {
    return m_hp;
}

void UI::addLogMessage(std::string message) {
    // Adds newest log message to the front
    m_log.insert(m_log.begin(), message);

    // Keeps only the 6 most recent messages
    if (m_log.size() > 6) {
        m_log.pop_back();
    }
}

int UI::eventHandler(const df::Event* p_e) {
    return 0;
}

void UI::setHeroPosition(df::Vector pos){
    m_hero_pos = pos;
}

void UI::setMapSprite(std::string sprite_label){
    m_map_sprite_label = sprite_label;
}