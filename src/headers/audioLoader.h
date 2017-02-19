#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>

class AudioLoader{



public:
    AudioLoader(std::string);
    void start();
private:
    Mix_Chunk* audio;
};
