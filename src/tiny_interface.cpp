#include "../include/tiny_interface.h"
#include <iostream>

TinyInterface::TinyInterface(){
    
}

int TinyInterface::init(SDL_Renderer* renderer, Vector position, Vector size){
    if(renderer){
        this->renderer = renderer;
        this->position = position;
        this->size = size;
        return 0;
    }

    Logger::print(Logger::ERROR, "Renderer is nullptr");
    return -1;
}

void TinyInterface::update(){
    for(size_t i = 0; i < stash_modules.size(); i++){
        stash_modules[i]->update();
    }
}

void TinyInterface::render(){
    for(size_t i = 0; i < stash_modules.size(); i++){
        stash_modules[i]->render();
    }
}

bool TinyInterface::operator == (const TinyInterface& other){
    return this->id == other.id;
}

size_t TinyInterface::get_unique_id(){
    size_t max = 0;
    for(size_t i = 0; i < stash_modules.size(); i++){
        if(stash_modules[i]->id > max){
            max = stash_modules[i]->id;
        }
    }

    return max + 1;
}
