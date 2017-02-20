#include "score.h"

#include <iostream>
#include <string>

Score::Score(int finalScore){
    // set the score
    score = finalScore;
    std::cout << score << std::endl;
    // background sprite
    background = new Background();

    // music variables
    bpm = 100;
    crotchet = static_cast<float>(60)/static_cast<float>(bpm);
    beat = 0;
    // start the music
    std::string musicPath = "../music/track002.wav";
    audio = Mix_LoadWAV(musicPath.c_str());
    Mix_PlayChannel(2, audio, -1);
    startTick = SDL_GetTicks();
    // this doesn't really display the score, just sets the score vector
    displayScore();
}

void Score::exit(){
    Mix_FreeChunk(audio);
}

void Score::handleEvents(SDL_Event event){
    // go to the menu if a button was pressed
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_SPACE){
            Menu * menu = new Menu();
            nextState = menu;
            quit = true;
        }
    }
}

void Score::update(float delta){
    // keep track of the current beat in the song
    currentTick = static_cast<float>(SDL_GetTicks() - startTick)/1000.0;
    if(beat*crotchet < currentTick){
        background->changeDirection();
        beat++;
    }
}

void Score::render(SDL_Surface* display){
    // render the background
    background->render(display);
    for(int i = 0; i < scoreVector.size(); i++){
        scoreVector.at(i)->render(display, {});
    }
}

void Score::displayScore(){
    // display the score in number form
    std::string scoreString = std::to_string(score);
    for(int i = 0; i < scoreString.size(); i++){
        int key = scoreString[i] - '0';
        switch(key){
            case 0:{
                Sprite * temp = new Sprite("../art/0.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 1:{
                Sprite * temp = new Sprite("../art/1.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 2:{
                Sprite * temp = new Sprite("../art/2.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 3:{
                Sprite * temp = new Sprite("../art/3.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 4:{
                Sprite * temp = new Sprite("../art/4.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 5:{
                Sprite * temp = new Sprite("../art/5.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 6:{
                Sprite * temp = new Sprite("../art/6.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 7:{
                Sprite * temp = new Sprite("../art/7.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 8:{
                Sprite * temp = new Sprite("../art/8.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
            case 9:{
                Sprite * temp = new Sprite("../art/9.png");
                temp->setPos(500 + i * 64, 200);
                scoreVector.push_back(temp);
            } break;
        }
    }
}
