#include "Tutorial.h"

#include <iostream>
#include <string>
#include <cmath>

Tutorial::Tutorial(){
    std::string musicPath = "music/tutorial.wav";
    audio = Mix_LoadWAV(musicPath.c_str());
}

void Tutorial::init() {
    // temporary variables
    bpm = 80;
    crotchet = static_cast<float>(60)/static_cast<float>(bpm);
    // set the sprites and stuff
    background = new Background();
    bear = new Bear();
    bear->setPos(800, 90);
    sprites.push_back(bear);
    // set the cake textures
    cake1 = new Sprite("art/cake001.png");
    cake2 = new Sprite("art/cake002.png");
    cake3 = new Sprite("art/cake003.png");
    // set the beat map and beat data
    loadTypeMap();
    loadCakes();
    loadBeatMap();
    beatMapIndex = 0;
    nextBeat = beatMap.at(beatMapIndex);
    lastBeat = nextBeat;
    beat = 0;
    start();
}

void Tutorial::exit(){

}

void Tutorial::handleEvents(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_SPACE){
            if(!press1){
                mainPress();
                press1 = true;
            }
        }else{
            // back to start menu
            TempState * next = new TempState();
            nextState = next;
            quit = true;
        }
    }
    if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_SPACE){
            press1 = false;
        }
    }
}

void Tutorial::update(float delta){
    currentTick = static_cast<float>(SDL_GetTicks() - startTick)/1000.0;
    // update the current beat if necessary
    if((nextBeat-1)*crotchet < currentTick){
        beatMapIndex++;
        lastBeat = nextBeat;
        // go to the next beat if there are any left
        if(beatMapIndex < beatMap.size()){
            nextBeat = beatMap.at(beatMapIndex);
        }
        // eat a cake when the next beat is reached
        eatCake();
    }
    // keep track of the current beat in the song
    if(beat*crotchet < currentTick){
        background->changeDirection();
        // update the bear sprite if tile is right
        if(beat % 2 == 0){
            bear->readyEat();
        }
        beat++;
    }
    // update each sprite
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i)->update(delta);
    }
    // delete sprites if they should be deleted
    for(int i = sprites.size()-1; i >= 0; i--){
        if(sprites.at(i)->shouldRemove()){
            sprites.erase(sprites.end()-i);
        }
    }
}

void Tutorial::render(SDL_Surface* display){
    background->render(display);
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i)->render(display, {});
    }
    renderCakes(display);
}

void Tutorial::mainPress(){
    // calculate the time at which the press occured
    int cTick = static_cast<int>(SDL_GetTicks() - startTick);
    int offset = 750;
    // calculate the difference between press and next beat
    int difference2 = std::abs(nextBeat * crotchet * 1000 - offset - cTick);
    int difference1 = std::abs(lastBeat * crotchet * 1000 - offset - cTick);
    int difference = difference1 > difference2 ? difference2 : difference1;
    std::cout << difference << std::endl;
    // add a text corresponding to how well the player did
    if(difference >= 100){
        Text * text = new Text("art/fail.png", 300);
        text->setPos(100, 500);
        sprites.push_back(text);
    }else if(difference > 40){
        Text * text = new Text("art/good.png", 400);
        text->setPos(100, 500);
        sprites.push_back(text);
    }else{
        Text * text = new Text("art/delicious.png", 400);
        text->setPos(100, 500);
        sprites.push_back(text);
    }
    bear->eat();
    // play a beat
	Mix_Chunk *tempWave = Mix_LoadWAV("music/beat.wav");
	// check to see if the music successfully loaded
	if (tempWave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_PlayChannel(1, tempWave, 0) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
}

void Tutorial::loadBeatMap(){
    for(int i = 0; i < typeMap.size(); i++){
        int key = typeMap.at(i);
        if(key == 0){
            beatMap.push_back(static_cast<float>((i+1) * 2));
        }
        if(key == 1){
            beatMap.push_back(static_cast<float>((i+1) * 2));
            beatMap.push_back(static_cast<float>((i+1) * 2 + 0.5));
        }
        if(key == 2){
            beatMap.push_back(static_cast<float>((i+1) * 2 + 0.5));
        }
    }
}

void Tutorial::loadCakes(){
    for(int i = 0; i < typeMap.size(); i++){
        if(typeMap.at(i) == 0){
            cakeStack.push_back(0);
        }
        else if(typeMap.at(i) == 1){
            cakeStack.push_back(1);
            cakeStack.push_back(1);
        }
        else if(typeMap.at(i) == 2){
            cakeStack.push_back(2);
        }
    }
}

// eat a cake from the cake stack
void Tutorial::eatCake(){
    if(cakeStack.size() > 0){
        cakeStack.erase(cakeStack.begin());
    }
}

// render cakes depending on what the current cake stack looks like
void Tutorial::renderCakes(SDL_Surface* display){
    int stackSize = cakeStack.size();
    // render the cakes that will show on screen
    for(int i = 0; i < 7; i++){
        if(i < stackSize){
            int key = cakeStack.at(i);
            if(key == 0){
                cake1->setPos(800, i*110+200);
                cake1->render(display, {});
            }
            else if(key == 1){
                cake2->setPos(800, i*110+200);
                cake2->render(display, {});
            }
            else if(key == 2){
                cake3->setPos(800, i*110+200);
                cake3->render(display, {});
            }
        } else {
            cake1->setPos(800, i*110+200);
            cake1->render(display, {});
        }
    }
}

// start the game
void Tutorial::start(){
    // start the music and timer
    Mix_PlayChannel(2, audio, -1);
    startTick = SDL_GetTicks();
}

void Tutorial::loadTypeMap(){
    for(int i = 0; i < 150; i++){
        typeMap.push_back(0);
        typeMap.push_back(1);
        typeMap.push_back(0);
        typeMap.push_back(2);
    }
}
