#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "sprite.h"
#include "animatedSprite.h"
#include "state.h"
#include "menu.h"

class Score : public State{

public:
    Score(int);
    void exit();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*);
private:
    int score;
    std::vector<Sprite*> scoreVector;

    Background * background;

    int bpm;
    float crotchet;
    Uint32 startTick;
    float currentTick;
    int beat;

    Mix_Chunk * audio;

    void displayScore();
};
