#include "engine.h"

#include <string>
#include <iostream>

Engine::Engine(){

}

bool Engine::init(){

    // initialize SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }else{
        // create a game window
        gWindow = SDL_CreateWindow("Heaven's Edge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr){
            std::cout << "Window initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }
        display = SDL_GetWindowSurface(gWindow);
        // initialize image loading library
        int success = IMG_Init(IMG_INIT_PNG);
        if(success&IMG_INIT_PNG != IMG_INIT_PNG){
            std::cout << "Image initialization failed: " << IMG_GetError() << std::endl;
            return false;
        }
        // initialize audio library
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0){
            std::cout << "Audio initialization failed: " << Mix_GetError() << std::endl;
            return false;
        }
    }
    // set a window icon
    std::string iconPath = "art/icon.png";
    SDL_Surface* icon = IMG_Load(iconPath.c_str());
    SDL_SetWindowIcon(gWindow, icon);
    // initialzie delta time calculating variables
    currentTime = SDL_GetTicks();
    lastTime = currentTime;
    return true;
}

void Engine::setState(State* state) {
    // set intiial state of game engine
    this->currentState = state;
    this->currentState->init();
    this->running = true;
    return;
}

void Engine::cleanUp(){
    // clean up SDL resources
}

void Engine::handleEvents(){
    // temporary code to escape window when escape key pressed or window quit
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            running = false;
        }
        this->currentState->handleEvents(e);
    }
}

void Engine::update(){
    currentTime = SDL_GetTicks();
    deltaTime = static_cast<float>(currentTime - lastTime)/1000.0;
    lastTime = currentTime;
    // TODO: replace temp float with delta time
    this->currentState->update(deltaTime);
    // check to see if the state should be changed
    if(this->currentState->shouldQuit()){
        this->currentState->exit();
        State * nextState = this->currentState->getNextState();
        if(nextState){
            this->currentState = nextState;
            this->currentState->init();
        }else{
            running = false;
        }
    }
}

void Engine::render(){
    // Fill the window black before updating the WINDOW
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
    this->currentState->render(display);
    SDL_UpdateWindowSurface(gWindow);
}

bool Engine::isRunning(){
    return this->running;
}
