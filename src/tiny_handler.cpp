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

int TinyHandler::free(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "interface argument is nullptr");
        return -1;
    }

    for(size_t i = 0; i < stash.size(); i++){
        TinyInterface* stash_interface = stash[i];
        if(interface == stash_interface){
            delete interface;
            interface = nullptr;
            stash.erase(stash.begin() + i);
            return 0;
        }
    }
    Logger::print(Logger::ERROR, "Couldnt find interface in the stash");
    return -1;
}

int TinyHandler::free_by_id(size_t id){
    if(id < 0){
        Logger::print(Logger::ERROR, "interface id < 0");
        return -1;
    }

    for(size_t i = 0; i < stash.size(); i++){
        TinyInterface* interface = stash[i];
        if(interface->id == id){
            delete interface;
            interface = nullptr;
            stash.erase(stash.begin() + i);
            return 0;
        }
    }
    Logger::print(Logger::ERROR, "Couldnt find interface in the stash");
    return -1;
}

int TinyHandler::free_all(){
    for(size_t i = 0; i < stash.size(); i++){
        TinyInterface* interface = stash[i];
        delete interface;
        interface = nullptr;
        stash.erase(stash.begin() + i);
    }

    if(stash.size() != 0){
        Logger::print(Logger::ERROR, "Stash is not empty");
        return -1;
    }

    return 0;
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

int TinyHandler::remove(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "interface argument is nullptr");
        return -1;
    }

    int index = contains(interface);
    if(index < 0){
        Logger::print(Logger::ERROR, "Failed to remove inteface from tiny holder.");
        return -1;
    }

    stash.erase(stash.begin() + index);
    return 0;
}

int TinyHandler::contains(TinyInterface* interface){
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i] == interface) return i;
    }
    return -1;
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