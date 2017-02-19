#include "AudioLoader.h"

#include <iostream>

AudioLoader::AudioLoader(std::string path){
    audio = Mix_LoadWAV(path.c_str());
    if(!audio){
        std::cout << "audio file failed to load" << Mix_GetError() << std::endl;
    }
}

void AudioLoader::start(){
    if(Mix_PlayChannel(2, audio, 0) == -1){
        std::cout << "audio file failed to play" << Mix_GetError() << std::endl;
    }
}
