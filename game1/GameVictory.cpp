//Engine includes
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
//Game includes
#include "GameVictory.h"
#include "GameStart.h"
#include "UI.h"

GameVictory::GameVictory(){
    setType("GameVictory");

    //Stop explore music
    df::Music* p_explore_music = RM.getMusic("music-explore");
    if (p_explore_music != nullptr)
        p_explore_music->stop();
    //Stop enemy music
    df::Music* p_enemy_music = RM.getMusic("music-enemy");
    if (p_enemy_music != nullptr)
        p_enemy_music->stop();
    //Stop boss music
    df::Music* p_boss_music = RM.getMusic("music-boss");
    if (p_boss_music != nullptr)
        p_boss_music->stop();
    
    //Play win music
    df::Music* p_win_music = RM.getMusic("music-win");
    if (p_win_music != nullptr)
        p_win_music->play(false);

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


    // Match GameOver duration (300 ticks = 10 seconds at 30 fps)
    time_to_live = 300;

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
            p_ui->addLogMessage("in 10 seconds.");
            p_ui->addLogMessage("Returning to title");
            p_ui->addLogMessage("YOU WIN!");
            p_ui->addLogMessage("CONGRATULATIONS");
            p_ui->addLogMessage("Its the CLAY POOL!");
        }
    }
}

GameVictory::~GameVictory(){
    //remove objects, re-activate gamestart
    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i < object_list.getCount(); i++){
        df::Object* p_o = object_list[i];
        if (p_o->getType() == "Map" || p_o->getType() == "Hero" || p_o->getType() == "UI" || p_o->getType() == "enemy" || p_o->getType() == "Reticle" || p_o->getType() == "Fountain" || p_o->getType() == "Clue" || p_o->getType() == "ColorClue" || p_o->getType() == "Keypad" || p_o->getType() == "KeypadButton")
            WM.markForDelete(p_o);
        if (p_o->getType() == "GameStart"){
            p_o->setActive(true);
            dynamic_cast<GameStart*>(p_o)->playMusic(); //resume start music
        }
    }
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
