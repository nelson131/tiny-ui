#include "../include/tiny_text.h"
#include <iostream>

TinyText::TinyText(){

}

int TinyText::create(SDL_Renderer* renderer, const char* font_path, std::string content){
    if(!renderer){
        Logger::print(Logger::ERROR, "Renderer is nullptr in text create");
        return -1;
    } this->renderer = renderer;

    if(!TTF_WasInit()){
        if(TTF_Init() == -1){
            Logger::print(Logger::ERROR, "TTF init failed: -1");
            return -1;
        }
    }

    font = TTF_OpenFont(font_path, 15);
    if(!font){
        Logger::print(Logger::ERROR, "Failed to open font (path:", font_path, ")");
        return -1;   
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, content.c_str(), white);
    if(!surface){
        Logger::print(Logger::ERROR, "Failed to load surface in text creating: ", content);
        return -1;
    }

    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);

    return 0;
}

void TinyText::update(SDL_Rect& rect){
    this->rect.x = rect.x;
    this->rect.y = rect.y;
}

void TinyText::render(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

int TinyText::clear(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if(font){
        TTF_CloseFont(font);
        font = nullptr;
    }

    TTF_Quit();
    return 0;
}