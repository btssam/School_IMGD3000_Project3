//Engine includes
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
//Game includes
#include "GameVictory.h"
#include "UI.h"

GameVictory::GameVictory(){
    setType("GameVictory");

    // Configure animation layers
    df::Sprite* p_base_sprite = RM.getSprite("claypool_base");
    if (p_base_sprite != nullptr) {
        m_base_anim.setSprite(p_base_sprite);
    }

    df::Sprite* p_clay_sprite = RM.getSprite("claypool_clay");
    if (p_clay_sprite != nullptr) {
        m_clay_anim.setSprite(p_clay_sprite);
    }

    df::Sprite* p_x_sprite = RM.getSprite("claypool_X");
    if (p_x_sprite != nullptr) {
        m_x_anim.setSprite(p_x_sprite);
    }

    df::Sprite* p_sparkles_sprite = RM.getSprite("claypool_sparkles");
    if (p_sparkles_sprite != nullptr) {
        m_sparkles_anim.setSprite(p_sparkles_sprite);
    }

    // Set primary sprite for base box and centering
    setSprite("claypool_base");


    // Match GameOver duration (720 ticks = 24 seconds at 30 fps)
    time_to_live = 720;

    setPosition(df::Vector(41, 10.5));
    setAltitude(df::MAX_ALTITUDE);
    registerInterest(df::STEP_EVENT);

    // Remove reticle immediately so combat stops
    df::ObjectList reticles = WM.objectsOfType("Reticle");
    for (int i = 0; i < reticles.getCount(); i++) {
        df::Object* p_reticle = reticles[i];
        WM.markForDelete(p_reticle);
    }

    // Disable hero movement during victory
    df::ObjectList heroes = WM.objectsOfType("Hero");
    for (int i = 0; i < heroes.getCount(); i++) {
        df::Object* p_hero = heroes[i];
        p_hero->setActive(false);
    }

    // Add victory messages to UI log
    df::ObjectList ui_list = WM.objectsOfType("UI");
    if (ui_list.getCount() > 0) {
        UI* p_ui = dynamic_cast<UI*>(ui_list[0]);
        if (p_ui != nullptr) {
            p_ui->addLogMessage("in 24 seconds.");
            p_ui->addLogMessage("The game will quit");
            p_ui->addLogMessage("YOU WIN!");
            p_ui->addLogMessage("CONGRATULATIONS");
            p_ui->addLogMessage("Its the CLAY POOL!");
        }
    }
}

GameVictory::~GameVictory(){
    //remove objects, end game
    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i < object_list.getCount(); i++){
        df::Object* p_o = object_list[i];
        if (p_o->getType() == "Map" || p_o->getType() == "Hero" || p_o->getType() == "UI" || p_o->getType() == "enemy" || p_o->getType() == "Reticle")
            WM.markForDelete(p_o);
    }
    GM.setGameOver(true);
}

int GameVictory::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

void GameVictory::step(){
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

int GameVictory::draw(){
    // Draw all 4 layers from bottom to top
    m_base_anim.draw(getPosition());
    m_clay_anim.draw(getPosition());
    m_x_anim.draw(getPosition());
    m_sparkles_anim.draw(getPosition());
    return 0;
}
