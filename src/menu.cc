#include "menu.h"

#include <iostream>

Menu::Menu(){
    // play item
    Sprite * play = new Sprite("art/play.png");
    play->setPos(700, 350);
    menuItem * item1 = new menuItem({0, nullptr, nullptr, play});
    selected = item1;
    // tutorial item
    Sprite * tutorial = new Sprite("art/tutorial.png");
    tutorial->setPos(700, 450);
    menuItem * item2 = new menuItem({1, item1, nullptr, tutorial});
    item1->next = item2;
    // quit item
    Sprite * quit = new Sprite("art/quit.png");
    quit->setPos(700, 550);
    menuItem * item3 = new menuItem({2, item2, nullptr, quit});
    item2->next = item3;
    // selector icon
    selector = new Sprite("art/icon.png");
    updateSelector();
    // background sprite
    background = new Background();
    // title sprite
    title = new Sprite("art/title.png");
    title->setPos(0, 20);

    // music variables
    bpm = 100;
    crotchet = static_cast<float>(60)/static_cast<float>(bpm);
    beat = 0;
    // start the music
    std::string musicPath = "music/track002.wav";
    audio = Mix_LoadWAV(musicPath.c_str());
    Mix_PlayChannel(2, audio, -1);
    startTick = SDL_GetTicks();
}

void Menu::exit(){
    Mix_FreeChunk(audio);
}

void Menu::handleEvents(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_UP){
            playBlip();
            if(selected->previous){
                selected = selected->previous;
            }
        }
        if(event.key.keysym.sym == SDLK_DOWN){
            playBlip();
            if(selected->next){
                selected = selected->next;
            }
        }
        if(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_a){
            std::cout << "PRESSED" << std::endl;
            select();
        }
        updateSelector();
    }
}

void Menu::update(float delta){
    // keep track of the current beat in the song
    currentTick = static_cast<float>(SDL_GetTicks() - startTick)/1000.0;
    if(beat*crotchet < currentTick){
        background->changeDirection();
        beat++;
    }
}

void Menu::render(SDL_Surface* display){
    // render the background
    background->render(display);
    // render the title
    title->render(display, {});
    // render the selected element
    selected->sprite->render(display, {});
    // render the previous menu items
    menuItem * currentItem = selected->previous;
    while(currentItem){
        currentItem->sprite->render(display, {});
        currentItem = currentItem->previous;
    }
    // render the next menu items
    currentItem = selected->next;
    while(currentItem){
        currentItem->sprite->render(display, {});
        currentItem = currentItem->next;
    }
    // render other things too
    selector->render(display, {});
}

void Menu::updateSelector(){
    int newY = selected->sprite->getY()-20;
    selector->setPos(550, newY);
}

void Menu::select(){
    int key = selected->index;
    // play the game
    if(key == 0){
        Level * temp = new Level();
        nextState  = temp;
        quit = true;
    }
    // tutorial level
    if(key == 1){
        Tutorial * temp = new Tutorial();
        nextState  = temp;
        quit = true;
    }
    // quit game
    if(key == 2){
        nextState = nullptr;
        quit = true;

    }
    // play a transition sound
    Mix_Chunk *tempWave = Mix_LoadWAV("music/select.wav");
    // check to see if the music successfully loaded
    if (tempWave == nullptr) {
        std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
        return;
    }
    if (Mix_PlayChannel(1, tempWave, 0) == -1) {
        std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
    }

}

void Menu::playBlip(){
    // play a blip
	Mix_Chunk *tempWave = Mix_LoadWAV("music/blip.wav");
	// check to see if the music successfully loaded
	if (tempWave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_PlayChannel(1, tempWave, 0) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
}
