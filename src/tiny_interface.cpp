#include "../include/tiny_interface.h"
#include <iostream>

TinyInterface::TinyInterface(){
    
}

bool TinyInterface::operator == (const TinyInterface& other){
    return this->id == other.id;
}