#include "text.h"

#include <iostream>

Text::Text(std::string path, int time) : Sprite(path){
    startTime = SDL_GetTicks();
    totalTime = time;
}

void Text::update(float delta){
    int cTime = SDL_GetTicks();
    if(cTime - startTime < totalTime){
        SDL_SetSurfaceAlphaMod(img, 255 - static_cast<float>(cTime-startTime)/totalTime * 255);
    }else{
        REMOVE = true;
    }
}
