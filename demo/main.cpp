#include <iostream>
#include <tiny_ui.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int init_window(SDL_Window** window, SDL_Renderer** renderer);
void handle_event(SDL_Event& event, bool& is_running);

int main(){
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    bool is_running = true;

    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
    atexit(SDL_Quit);
    if(init_window(&window, &renderer) < 0) return -1;

    // Initialize the TinyUI >>>
    TinyUI tiny_ui; // Creating an tiny ui main object
    tiny_ui.init(renderer, WINDOW_WIDTH, WINDOW_HEIGHT); // Initializing the renderer and window size
    
    // Create the Tiny Interface >>>
    Vector position = {0, 0}; // Using vector struct
    Vector size = {600, 700};
    TinyInterface* interface = tiny_ui.create_interface(position, size); // Creating an interface

    /*
    All types of TinyUI Modules.
    Created with func -> create_module<TinyModule::Type>(arguments)
    */

    // Image Module >>>
    auto image_module = interface->create_module<TinyModule::Image>( // Creating a module
        // Unique arguments for this module
        "assets/rabbit.jpg", // -> path to texture
        position, // -> position relative to interface position
        size // -> size of module, cant be bigger than interface ofc
    );

    // Text Module >>>
    auto text_module = interface->create_module<TinyModule::Text>(
        "assets/font.ttf",
        "HalfLife 3 confirmed",
        position,
        size
    );

    // Main loop of your program
    while(is_running){
        // Event logic >>>
        handle_event(event, is_running);
        // Update logic >>>
        tiny_ui.update(); // Update tiny interfaces
        // Render logic >>>
        SDL_RenderClear(renderer);

        tiny_ui.render(); // Render tiny interfaces

        SDL_RenderPresent(renderer);
    }

    tiny_ui.clean_up(); // Clean up your program: deletes all interfaces

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

int init_window(SDL_Window** window, SDL_Renderer** renderer){
    SDL_Init(SDL_INIT_EVERYTHING);

    *window = SDL_CreateWindow(
        "Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if(!renderer){
        std::cout << "renderer is nullptr guys" << std::endl;
        return -1;
    }

    return 0;
}

void handle_event(SDL_Event& event, bool& is_running){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                is_running = false;
                break;
            default:
                break;
        }
    }
}