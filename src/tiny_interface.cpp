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

template<typename T, typename... Args>
T* TinyInterface::create_module(Args&&... args){
    static_assert(std::is_base_of_v<TinyModule::Base, T>, "T must be part of TinyModule::Base");

    auto module = std::make_unique<T>(std::forward<Args>(args)...);
    if(module->init(renderer, this) < 0){
        Logger::print(Logger::ERROR, "Failed to create a module (InterfaceID:", id, ")");
        return nullptr;
    }
    T* raw = module.get();

    stash_modules.push_back(std::move(module));
    return raw;
}

bool TinyInterface::operator == (const TinyInterface& other){
    return this->id == other.id;
}