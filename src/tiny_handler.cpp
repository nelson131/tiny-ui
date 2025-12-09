#include "../include/tiny_handler.h"
#include <iostream>

TinyHandler::TinyHandler(){

}

void TinyHandler::add(TinyInterface interface){
    interface.id = get_unique_id();
    stash.push_back(interface);
}

void TinyHandler::remove(TinyInterface interface){
    int index = contains(interface);
    if(index < 0){
        Logger::print(Logger::ERROR, "Failed to remove inteface from tiny holder.");
        return;
    }

    stash.erase(stash.begin() + index);
}

int TinyHandler::contains(TinyInterface& interface){
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i] == interface) return i;
    }
    return -1;
}

int TinyHandler::get_unique_id(){
    if(stash.empty()) return 1;
    
    int unique = 1;
    for(size_t i = 0; i < stash.size(); i++){
        if(stash[i].id > unique){
            unique = stash[i].id;
        }
    }

    return unique++;
}