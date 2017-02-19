#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "sprite.h"

// text class that fades out
class Text : public Sprite{

public:
    Text(std::string, int);

    void update(float);
private:
    Uint32 startTime;
    int totalTime;
};
