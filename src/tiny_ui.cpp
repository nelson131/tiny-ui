#include "../include/tiny_ui.h"

TinyUI::TinyUI(){

}

TinyUI::TinyUI(SDL_Renderer* renderer, size_t window_width, size_t window_height)
    : renderer(renderer), window_width(window_width), window_height(window_height)
{

}

void TinyUI::init(SDL_Renderer* renderer, size_t window_width, size_t window_height){
    this->renderer = renderer;
    this->window_width = window_width;
    this->window_height = window_height;
}

void TinyUI::update(){
    tiny_handler.update();   
}

void TinyUI::render(){
    tiny_handler.render();
}

void TinyUI::clean_up(){
    if(tiny_handler.free_all() == -1){
        Logger::print(Logger::ERROR, "Failed to free all interfaces");
    }
}

TinyInterface* TinyUI::create_interface(Vector position, Vector size){
    TinyInterface* interface = new TinyInterface();
    interface->init(renderer, position, size);

    tiny_handler.add(interface);
}