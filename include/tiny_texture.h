#ifndef TINY_TEXTURE_H
#define TINY_TEXTURE_H

#include "tiny_logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class TinyTexture {
    public:
    static SDL_Texture* load(std::string path, SDL_Renderer* renderer){
        SDL_Surface* surface = IMG_Load(path.c_str());
        if(!surface){
            Logger::print(Logger::ERROR, "Failed to load surface in texture manager -> ", path);
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(!texture){
            Logger::print(Logger::ERROR, "Failed to load texture in texture manager -> ", path);
            return nullptr;
        }

        return texture;
    }

    static SDL_Texture* load(std::string path, SDL_Renderer* renderer, int& w, int& h){
        SDL_Surface* surface = IMG_Load(path.c_str());
        if(!surface){
            Logger::print(Logger::ERROR, "Failed to load surface in texture manager -> ", path);
            return nullptr;
        }
        w = surface->w;
        h = surface->h;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(!texture){
            Logger::print(Logger::ERROR, "Failed to load texture in texture manager -> ", path);
            return nullptr;
        }

        return texture;
    }
};

#endif