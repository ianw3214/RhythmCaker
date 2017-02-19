#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>
#include <string>

#include "sprite.h"

class Background{

public:
    Background();
    void changeDirection();

    void update(float);
    void render(SDL_Surface*);
private:
    bool flip;
    std::vector<Sprite*> sprites;

    float deltaTime;
};
