#include "../include/tiny_text.h"
#include <iostream>

Text::Text(){

}

int Text::create(std::string font_path, std::string content){
    if(TTF_Init() == -1){
        Logger::print(Logger::ERROR, "TTF init failed: -1");
        return -1;
    }

    font = TTF_OpenFont(font_path.c_str(), 15);
    if(!font){
        Logger::print(Logger::ERROR, "Failed to open font (path:", font_path, ")");
        return -1;   
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, content.c_str(), white);
    if(!surface){
        Logger::print(Logger::ERROR, "Failed to load surface in text creating: ", content);
        return -1;
    }
}