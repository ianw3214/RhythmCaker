#include "level.h"

#include <iostream>
#include <string>
#include <cmath>

Level::Level(){
    music = new AudioLoader("../music/track001.wav");
}

void Level::init() {
    // temporary variables
    bpm = 120;
    crotchet = static_cast<float>(60)/static_cast<float>(bpm);
    // set the sprites and stuff
    background = new Background();
    bear = new Bear();
    bear->setPos(800, 90);
    sprites.push_back(bear);
    // set the cake textures
    cake1 = new Sprite("../art/cake001.png");
    cake2 = new Sprite("../art/cake002.png");
    cake3 = new Sprite("../art/cake003.png");
    text_GOOD = new Sprite("../art/good.png");
    // set the beat map and beat data
    typeMap = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 1, 1};
    typeMap = {0, 0};
    loadCakes();
    loadBeatMap();
    beatMapIndex = 0;
    nextBeat = beatMap.at(beatMapIndex);
    lastBeat = nextBeat;
    beat = 0;
    // variables to handle ticking before game starts
    preBeat = 0;
    started = false;
    preStartTick = SDL_GetTicks();
    // set initial variables
    gameOver = false;
    overCounter = 0;
    nextStateTime = 0.0f;
    score = 0;
}

void Level::exit(){

}

void Level::handleEvents(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_SPACE){
            if(!press1){
                mainPress();
                press1 = true;
            }
        }
    }
    if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_SPACE){
            press1 = false;
        }
    }
}

void Level::update(float delta){
    if(started){
        currentTick = static_cast<float>(SDL_GetTicks() - startTick)/1000.0;
        // update the current beat if necessary
        if((nextBeat-1)*crotchet < currentTick  && !gameOver){
            beatMapIndex++;
            lastBeat = nextBeat;
            // go to the next beat if there are any left
            if(beatMapIndex < beatMap.size()){
                nextBeat = beatMap.at(beatMapIndex);
            }else{
                if(overCounter < 2){
                    overCounter++;
                }else{
                    // game is over when no more beatmap
                    gameOver = true;
                }
            }
            // eat a cake when the next beat is reached
            eatCake();
        }
        if(gameOver){
            nextStateTime += delta;
            if(nextStateTime > 3){
                // go to game over screen
                goToScore();
            }
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
    }else{
        // the game is still in prebeat
        currentTick = static_cast<float>(SDL_GetTicks() - preStartTick)/1000.0;
        // keep track of the current beat in the song
        if(preBeat * crotchet < currentTick){
            background->changeDirection();
            // update the bear sprite if tile is right
            preBeat++;

            if(preBeat == 5){
                playTick();
                std::cout << "5" << std::endl;
            }
            if(preBeat == 6){
                playTick();
                std::cout << "6" << std::endl;
            }
            if(preBeat == 7){
                playTick();
                std::cout << "7" << std::endl;
            }
            if(preBeat == 8){
                playTick();
                std::cout << "8" << std::endl;
            }
            if(preBeat >= 9){
                start();
            }
        }
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

void Level::render(SDL_Surface* display){
    background->render(display);
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i)->render(display, {});
    }
    renderCakes(display);
    renderScore(display);
}

void Level::mainPress(){
    if(started && !gameOver){
        // calculate the time at which the press occured
        int cTick = static_cast<int>(SDL_GetTicks() - startTick);
        int offset = 500;
        // calculate the difference between press and next beat
        int difference2 = std::abs(nextBeat * crotchet * 1000 - offset - cTick);
        int difference1 = std::abs(lastBeat * crotchet * 1000 - offset - cTick);
        int difference = difference1 > difference2 ? difference2 : difference1;
        std::cout << difference << std::endl;
        // add a text corresponding to how well the player did
        if(difference >= 70){
            Text * text = new Text("../art/fail.png", 300);
            text->setPos(100, 500);
            sprites.push_back(text);
        }else if(difference >20){
            score += 100;
            Text * text = new Text("../art/good.png", 400);
            text->setPos(100, 500);
            sprites.push_back(text);
        }else{
            score += 500;
            Text * text = new Text("../art/delicious.png", 400);
            text->setPos(100, 500);
            sprites.push_back(text);
        }
    }
    bear->eat();
    // play a beat
	Mix_Chunk *tempWave = Mix_LoadWAV("../music/beat.wav");
	// check to see if the music successfully loaded
	if (tempWave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_PlayChannel(1, tempWave, 0) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
}

void Level::loadBeatMap(){
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

void Level::loadCakes(){
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
void Level::eatCake(){
    if(cakeStack.size() > 0){
        cakeStack.erase(cakeStack.begin());
    }
}

// render cakes depending on what the current cake stack looks like
void Level::renderCakes(SDL_Surface* display){
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
void Level::start(){
    started = true;
    // start the music and timer
    music->start();
    startTick = SDL_GetTicks();
}

void Level::playTick(){
    // play a tick
	Mix_Chunk *tempWave = Mix_LoadWAV("../music/tick.wav");
	// check to see if the music successfully loaded
	if (tempWave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_PlayChannel(2, tempWave, 0) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
}

void Level::goToScore(){
    // go to the score screen
    Score* scene = new Score(score);
    nextState = scene;
    quit = true;
}

void Level::renderScore(SDL_Surface* display){
    // display the score in number form
    std::string scoreString = std::to_string(score);
    for(int i = 0; i < scoreString.size(); i++){
        int key = scoreString[i] - '0';
        switch(key){
            case 0:{
                Sprite * temp = new Sprite("../art/0.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 1:{
                Sprite * temp = new Sprite("../art/1.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 2:{
                Sprite * temp = new Sprite("../art/2.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 3:{
                Sprite * temp = new Sprite("../art/3.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 4:{
                Sprite * temp = new Sprite("../art/4.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 5:{
                Sprite * temp = new Sprite("../art/5.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 6:{
                Sprite * temp = new Sprite("../art/6.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 7:{
                Sprite * temp = new Sprite("../art/7.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 8:{
                Sprite * temp = new Sprite("../art/8.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
            case 9:{
                Sprite * temp = new Sprite("../art/9.png");
                temp->setPos(100 + i * 64, 200);
                temp->render(display, {});
            } break;
        }
    }
}
