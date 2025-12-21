#ifndef TINY_UI_H
#define TINY_UI_H

#include "tiny_interface.h"
#include "tiny_handler.h"
#include <iostream>
#include <SDL2/SDL.h>

class TinyUI {
    public:
    TinyUI();
    TinyUI(SDL_Renderer* renderer, size_t window_width, size_t window_height);

    void init(SDL_Renderer* renderer, size_t window_width, size_t window_height);
    void update();
    void render();
    
    void free(TinyInterface* interface);
    void free_by_id(size_t id);
    void clean_up();

    TinyInterface* create_interface(Vector position, Vector size);

    int add_interface(TinyInterface* interface);
    int remove_interface(TinyInterface* interface);
    int contains_interface(TinyInterface* interface);
    TinyInterface* get_interface(size_t id);

    private:
    TinyHandler tiny_handler;

    SDL_Renderer* renderer = nullptr;

    size_t window_width = 0;
    size_t window_height = 0;
};

#endif