#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "sprite.h"
#include "animatedSprite.h"
#include "state.h"
#include "level.h"
#include "tutorial.h"

struct menuItem{
    int index;
    menuItem * previous;
    menuItem * next;
    Sprite* sprite;
};

class Menu : public State{

public:
    Menu();
    void exit();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*);
private:
    int menuLength;
    menuItem * selected;
    Sprite * selector;
    Background * background;
    Sprite * title;

    int bpm;
    float crotchet;
    Uint32 startTick;
    float currentTick;
    int beat;

    Mix_Chunk * audio;

    void updateSelector();
    void select();
    void playBlip();
};
