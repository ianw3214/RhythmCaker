#include "menu.h"

#include <iostream>

Menu::Menu(){
    // play item
    Sprite * play = new Sprite("../art/play.png");
    play->setPos(700, 300);
    menuItem * item1 = new menuItem({0, nullptr, nullptr, play});
    selected = item1;
    // tutorial item
    Sprite * tutorial = new Sprite("../art/tutorial.png");
    tutorial->setPos(700, 400);
    menuItem * item2 = new menuItem({1, item1, nullptr, tutorial});
    item1->next = item2;
    // quit item
    Sprite * quit = new Sprite("../art/quit.png");
    quit->setPos(700, 500);
    menuItem * item3 = new menuItem({2, item2, nullptr, quit});
    item2->next = item3;
    // selector icon
    selector = new Sprite("../art/icon.png");
    updateSelector();
}

void Menu::handleEvents(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_UP){
            if(selected->previous){
                selected = selected->previous;
            }
        }
        if(event.key.keysym.sym == SDLK_DOWN){
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

}

void Menu::render(SDL_Surface* display){
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
        std::cout << "TUTORIAL" << std::endl;
    }
    // quit game
    if(key == 2){
        nextState = nullptr;
        quit = true;

    }
}
