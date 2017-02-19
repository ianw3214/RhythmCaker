#include "bear.h"

#include <vector>

Bear::Bear() : AnimatedSprite("../art/bear_sheet.png", 256, 128, 4, false) {
    std::vector<int> animData = {1, 4};
    setAnimationData(animData);
}

void Bear::update(float delta){
    // completely override the animated sprite update function
    deltaTime += delta;
        // TODO: customize update frame rate
        if(deltaTime >= 0.03f){
            currentFrame++;
            if(currentFrame >= animData.at(currentAnim)){
                if(currentAnim == 1){
                    currentAnim = 0;
                }
                if(playOnce) REMOVE = true;
                currentFrame = 0;
            }
            deltaTime = 0.0f;
            updateBlitRect();
        }
}

void Bear::render(SDL_Surface * display, SDL_Rect camera){
    AnimatedSprite::render(display, {});
}

void Bear::readyEat(){
    currentAnim = 0;
}

void Bear::eat(){
    currentAnim = 1;
    currentFrame = 0;
    updateBlitRect();
}
