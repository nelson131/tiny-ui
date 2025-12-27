#include "../include/tiny_handler.h"
#include <iostream>

TinyHandler::TinyHandler(){

}

void TinyHandler::update(){
    for(size_t i = 0; i < stash.size(); i++){
        stash[i]->update();
    }
}

void TinyHandler::render(){
    for(size_t i = 0; i < stash.size(); i++){
        stash[i]->render();
    }
}

int TinyHandler::add(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "interface argument is nullptr");
        return -1;
    }

    interface->id = get_unique_id();
    stash.push_back(interface);
    return 0;
}

int TinyHandler::contains(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "Interface is nullptr. Failed to find it in stash");
        return -1;
    }

    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i] == interface) return i;
    }
    return -1;
}

TinyInterface* TinyHandler::get(size_t id){
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i]->id == id){
            return stash[i];
        }
    }

    return nullptr;
}

int TinyHandler::remove(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "interface argument is nullptr");
        return -1;
    }

    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i] == interface){
            delete stash[i];
            stash.erase(stash.begin() + i);
            return 0;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find interface (ID:", interface->id, ") to remove");
    return -1;
}

int TinyHandler::remove_by_id(size_t id){
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i]->id == id){
            delete stash[i];
            stash.erase(stash.begin() + i);
            return 0;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find interface (ID:", id, ") to remove");
    return -1;
}

int TinyHandler::remove_all(){
    for(size_t i = 0; i < stash.size(); i++){
        if(!stash[i]) continue;
        delete stash[i];
    }

    stash.clear();
    return 0;
}

int TinyHandler::get_unique_id(){
    if(stash.empty()) return 1;
    
    int unique = 1;
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i]->id > unique){
            unique = stash[i]->id;
        }
    }

    return unique++;
}