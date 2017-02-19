#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "animatedSprite.h"

class Bear : public AnimatedSprite{

public:
    Bear();

    void readyEat();
    void eat();

    void update(float);
    void render(SDL_Surface*, SDL_Rect);
private:

};
