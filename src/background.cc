#include "background.h"

#include <iostream>

Background::Background(){
    flip = true;
    // initialize the background with strawberry sprites
    for(int i = 0; i < 13; i++){
        int offset = i % 2 == 0 ? 100 : 0;
        for(int j = 0; j < 4; j++){
            Sprite* sprite = new Sprite("../art/strawberry.png");
            sprite->setPos(i*100, j * 200 + offset);
            sprites.push_back(sprite);
        }
    }
}

void Background::changeDirection(){
    flip = !flip;
    std::string path = flip ? "../art/strawberry.png" : "../art/strawberry_flip.png";
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i)->loadImage(path);
    }
}

void Background::render(SDL_Surface* display){
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i)->render(display, {});
    }
}
