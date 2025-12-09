#ifndef TINY_UI_H
#define TINY_UI_H

#include <iostream>
#include <SDL2/SDL.h>

class TinyUI {
    public:
    TinyUI();
    TinyUI(SDL_Renderer* renderer, size_t window_width, size_t window_height);

    void init(SDL_Renderer* renderer, size_t window_width, size_t window_height);

    private:
    SDL_Renderer* renderer = nullptr;

    size_t window_width = 0;
    size_t window_height = 0;
};

#endif