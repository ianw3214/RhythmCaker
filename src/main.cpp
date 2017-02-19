#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "engine.h"
#include "level.h"

int main(int argc, char* argv[]){

    Engine game;
    if(!game.init()){
        return 1;
    }
    Level* test = new Level();
    game.setState(test);
    while(game.isRunning()){
        game.handleEvents();
        game.update();
        game.render();
    }

    game.cleanUp();

    return 0;

}