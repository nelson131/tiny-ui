#ifndef TINY_TEXT_H
#define TINY_TEXT_H

#include "tiny_vector.h"
#include "tiny_logger.h"

#include <SDL2/SDL_ttf.h>
#include <string>

class TinyText {
    public:
    TinyText();

    Vector position = {0, 0};

    int create(SDL_Renderer* renderer, const char* font_path, std::string content);
    void update(SDL_Rect& rect);
    void render();
    int clear();

    private:
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect = {20, 20, 0, 0};
};

#endif