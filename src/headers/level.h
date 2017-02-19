#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "audioloader.h"
#include "state.h"
#include "bear.h"
#include "background.h"
#include "text.h"

class Level : public State {

public:
    Level();

    void init();
    void exit();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*);
private:
    AudioLoader* music;

    int bpm;
    float crotchet;

    Uint32 startTick;
    float currentTick;

    std::vector<int> typeMap;
    std::vector<int> cakeStack;
    std::vector<float> beatMap;
    int beatMapIndex, beat;
    float nextBeat, lastBeat;
    bool press1;
    int inputLag = 400;

    Background* background;
    std::vector<Sprite*> sprites;
    Bear* bear;

    Sprite* cake1;
    Sprite* cake2;
    Sprite* cake3;

    Sprite* text_GOOD;

    void mainPress();
    void loadBeatMap();
    void loadCakes();
    void eatCake();
    void renderCakes(SDL_Surface*);
};
