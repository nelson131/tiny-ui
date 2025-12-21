#include "./include/tiny_ui.h"

#include <iostream>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int init_window(SDL_Window* window, SDL_Renderer* renderer);

int main(){
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool is_running = true;

    if(init_window(window, renderer) == -1) return -1;

    TinyUI tiny_ui;

    tiny_ui.init(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Vector position = {100, 100};
    Vector size = {200, 200};
    TinyInterface* interface = tiny_ui.create_interface(position, size);

    while(is_running){
        tiny_ui.update();
        tiny_ui.render();
    }

    return 0;
}

int init_window(SDL_Window* window, SDL_Renderer* renderer){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
        "Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) return -1;

    return 0;
}