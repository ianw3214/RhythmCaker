#include "tempState.h"

TempState::TempState(){
    Menu * temp = new Menu();
    nextState = temp;
    quit = true;
}
