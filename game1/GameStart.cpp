//Handles starting the game, displays main menu sprite, and handles the story crawl
// Engine includes
#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "utility.h"
#include "Precipitation.h"

// Game includes
#include "GameStart.h"
#include "Hero.h"
#include "Map.h"
#include "UI.h"
#include "Reticle.h"

GameStart::GameStart(){
    setType("GameStart");
    setSprite("gamestart");
    setLocation(df::CENTER_CENTER);

    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    p_music_title = RM.getMusic("music-title");
    p_music_story = RM.getMusic("music-exposition");

    in_story = false;
    story_time_to_live = 0;

    playMusic();
}

int GameStart::eventHandler(const df::Event* p_e){
    if (p_e->getType() == df::KEYBOARD_EVENT){
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
        if (p_keyboard_event != nullptr && p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED){
            switch (p_keyboard_event->getKey()){
                case df::Keyboard::P:
                    if (!in_story)
                        startStory();
                    else
                        start(); //skip story
                    break;
                case df::Keyboard::Q:
                    GM.setGameOver(true);
                    break;
                default:
                    break;
            }
        }
        return 1;
    }

    if (p_e->getType() == df::STEP_EVENT){
        step();
        return 1;
    }

    return 0;
}

int GameStart::draw(){
    int res = df::Object::draw();

    //draw skip and quit hints during story crawl
    if (in_story){
        float x = WM.getBoundary().getHorizontal() - 2;
        float y = WM.getBoundary().getVertical() - 3;
        DM.drawString(df::Vector(x, y), "'p' to skip", df::RIGHT_JUSTIFIED, df::WHITE);
        DM.drawString(df::Vector(x, y + 1), "'q' to quit", df::RIGHT_JUSTIFIED, df::WHITE);
    }

    return res;
}

void GameStart::startStory(){
    //stop title music
    if (p_music_title != nullptr)
        p_music_title->stop();

    //play 45-second exposition track
    if (p_music_story != nullptr)
        p_music_story->play(false);

    //switch sprite to story text
    setSprite("story");

    //start at bottom of screen, cut off
    float start_x = WM.getBoundary().getHorizontal() / 2.0f;
    float start_y = WM.getBoundary().getVertical() + (getAnimation().getSprite()->getHeight() / 2.0f);
    setPosition(df::Vector(start_x, start_y));

    setDirection(df::Vector(0, -1));
    setSpeed(38.0f / 1350.0f);

    //set story timeout (45 seconds * 30 ticks/sec = 1350 ticks)
    //the music track is ~45 seconds
    story_time_to_live = 1350;
    in_story = true;
}

void GameStart::step(){
    if (in_story){
        story_time_to_live--;
        if (story_time_to_live <= 0){
            start();
        }
    }
}

void GameStart::start(){
    if (p_music_story != nullptr)
        p_music_story->stop();
    setVelocity(df::Vector(0, 0));

    //remove background particles when entering dungeon
    removeParticles();

    //spawn gameplay objects
    UI* p_ui = new UI();
    new Reticle();
    Map* p_map = new Map();
    new Hero(p_ui, p_map);

    //deactivate gamestart until routed back
    setActive(false);
    in_story = false;
}

void GameStart::playMusic(){
    //stop any previous ending music
    df::Music* p_gameover_music = RM.getMusic("music-gameover");
    if (p_gameover_music != nullptr)
        p_gameover_music->stop();
    df::Music* p_win_music = RM.getMusic("music-win");
    if (p_win_music != nullptr)
        p_win_music->stop();
    df::Music* p_story_music = RM.getMusic("music-exposition");
    if (p_story_music != nullptr)
        p_story_music->stop();

    //reset visual and stop movement
    setSprite("gamestart");
    setLocation(df::CENTER_CENTER);
    setVelocity(df::Vector(0, 0));
    in_story = false;

    //spawn background particles behind start screen
    spawnParticles();
    
    if (p_music_title != nullptr)
        p_music_title->play(true);
}

void GameStart::spawnParticles(){
    //only spawn if not already present in world
    if (WM.objectsOfType("Precipitation").getCount() == 0){
        df::addParticles(df::SNOW, df::DOWN);
        df::ObjectList particles = WM.objectsOfType("Precipitation");
        for (int i = 0; i < particles.getCount(); i++){
            df::Object* p_o = particles[i];
            p_o->setAltitude(1);
        }
    }
}

void GameStart::removeParticles(){
    //mark all precipitation particles for deletion
    df::ObjectList particles = WM.objectsOfType("Precipitation");
    for (int i = 0; i < particles.getCount(); i++){
        df::Object* p_o = particles[i];
        WM.markForDelete(p_o);
    }
}
