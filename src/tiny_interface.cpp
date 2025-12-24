#include "../include/tiny_interface.h"
#include <iostream>

TinyInterface::TinyInterface(){
    
}

void TinyInterface::init(SDL_Renderer* renderer, Vector position, Vector size){
    if(!renderer){
        Logger::print(Logger::ERROR, "Failed to load renderer in the interface (ID:", id, ")");
    } else {
        this->renderer = renderer;
    }
    this->position = position;
    this->size = size;
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