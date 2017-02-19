#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "sprite.h"
#include "animatedSprite.h"
#include "state.h"
#include "level.h"

struct menuItem{
    int index;
    menuItem * previous;
    menuItem * next;
    Sprite* sprite;
};

class Menu : public State{

public:
    Menu();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*);
private:
    int menuLength;
    menuItem * selected;
    Sprite * selector;

    void updateSelector();
    void select();
};
