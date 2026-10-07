// GameStart screen and handles starting the game and the intro story scroll
#pragma once

// Engine includes
#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
    private:
        //pointer to title screen music
        df::Music* p_music_title;
        //pointer to story exposition music
        df::Music* p_music_story;
        //true if currently displaying scrolling story
        bool in_story;
        //how long the story crawl should stay on screen before starting game (in frames)
        int story_time_to_live;

        //begins the scrolling story sequence
        void startStory();
        //actually launches the gameplay objects (Hero, UI, Map, Reticle)
        void start();
        //step event each frame (for story countdown)
        void step();

    public:
        //constructor
        GameStart();
        //event handler for keyboard and step events
        int eventHandler(const df::Event* p_e) override;
        //draw override (draws sprite and skip/quit prompts)
        int draw() override;
        //resets screen state and plays title music
        void playMusic();
};
