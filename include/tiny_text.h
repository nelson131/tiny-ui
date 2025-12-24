#ifndef TINY_TEXT_H
#define TINY_TEXT_H

#include "tiny_logger.h"

#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
    public:
    Text();

    int create(std::string font_path, std::string content);
    void render();
    int clear();

    private:
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect = {20, 20, 0, 0};
};

#endif