#include <iostream>
#include <tiny_ui.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int init_window(SDL_Window** window, SDL_Renderer** renderer);
void handle_event(SDL_Event& event, bool& is_running);
void event_test();
void event_test_s();

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
    Vector position = {0, 0}; // Using vector struct from tiny_vector.h
    Vector size = {600, 700};
    TinyInterface* interface = tiny_ui.create_interface(position, size); // Creating an interface

    /*
    All types of TinyUI Modules.
    Created with func -> create_module<TinyModule::Type>(arguments)
    */

    // Image Module >>>
    Vector img_position = {0, 0}; // Using vector struct from tiny_vector.h
    Vector img_size = {200, 200};
    auto image_module = interface->create_module<TinyModule::Image>( // Creating a module
        // Unique arguments for this module
        "assets/rabbit.jpg", // -> path to texture
        img_position, // -> position relative to interface position
        img_size, // -> size of module, cant be bigger than interface ofc
        true // -> image stretching <true/false>
    );

    // Creating an event for any module ->
    // args<Event_type, pointer to your func>   
    image_module->set_executor(EventType::CURSOR_LEAVE_EVENT, &event_test);
    image_module->set_executor(EventType::CLICK_EVENT, &event_test_s);

    // Text Module >>>
    Vector txt_position = {100, 100}; // Using vector struct from tiny_vector.h
    Vector txt_size = {300, 300};
    auto text_module = interface->create_module<TinyModule::Text>(
        // Unique arguments for this module
        "assets/font.ttf", // -> text font
        "HalfLife 3 confirmed", // -> content of module
        txt_position, // -> position relative to interface position
        txt_size // -> size of module
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

void event_test(){
    std::cout << "In the end it doesnt even matter" << std::endl;
}

void event_test_s(){
    std::cout << "This is my december" << std::endl;
}