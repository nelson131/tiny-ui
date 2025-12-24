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

    if(init_window(window, renderer) < 0) return -1;

    // Initialize the TinyUI >>>
    TinyUI tiny_ui; // Creating an tiny ui main object
    tiny_ui.init(renderer, WINDOW_WIDTH, WINDOW_HEIGHT); // Initializing the renderer and window size
    
    // Create the Tiny Interface >>>
    Vector position = {100, 100}; // Using vector struct
    Vector size = {200, 200};
    TinyInterface* interface = tiny_ui.create_interface(position, size); // Creating an interface

    // Add a module to interface >>>
    auto image_module = interface->create_module<TinyModule::Image>( // Creating a module
        // Unique arguments for this module
        "texture", // -> path to texture
        position, // -> position relative to interface position
        size // -> size of module, cant be bigger than interface ofc
    );

    // Main loop of your program
    while(is_running){
        tiny_ui.update(); // Updates tiny interfaces
        tiny_ui.render(); // Render tiny interfaces
    }

    tiny_ui.clean_up(); // Free all interfaces, modules, etc

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