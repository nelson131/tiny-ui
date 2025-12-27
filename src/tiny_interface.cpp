#include "../include/tiny_interface.h"
#include <iostream>

TinyInterface::TinyInterface(){
    
}

TinyInterface::~TinyInterface(){
    delete_all();
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

int TinyInterface::delete_module(TinyModule::Base* module){
    if(!module){
        Logger::print(Logger::ERROR, "Failed to delete module cause argument is nullptr");
        return -1;
    }

    for(size_t i = 0; i < stash_modules.size(); i++){
        if(stash_modules[i].get() == module){
            stash_modules.erase(stash_modules.begin() + i);
            return 0;
        }   
    }
    Logger::print(Logger::ERROR, "Failed to delete module: failed to find it");
    return -1;
}

int TinyInterface::delete_module_by_id(size_t id){
    for(size_t i = 0; i < stash_modules.size(); i++){
        if(stash_modules[i].get()->id == id){
            stash_modules.erase(stash_modules.begin() + i);
            return 0;
        }
    }
    Logger::print(Logger::ERROR, "Failed to delete module by id: failed to find it");
    return -1;
}

int TinyInterface::delete_all(){
    stash_modules.clear();
    return 0;
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
