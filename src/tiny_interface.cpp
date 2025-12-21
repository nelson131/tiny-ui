#include "../include/tiny_interface.h"
#include <iostream>

TinyInterface::TinyInterface(){
    
}

void TinyInterface::init(SDL_Renderer* renderer, Vector position, Vector size){
    this->renderer = renderer;
    this->position = position;
    this->size = size;
}

void TinyInterface::update(){

}

void TinyInterface::render(){

}

bool TinyInterface::operator == (const TinyInterface& other){
    return this->id == other.id;
}