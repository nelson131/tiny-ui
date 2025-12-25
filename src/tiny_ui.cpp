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

    Logger::print(Logger::SUCCESS, "TinyUI was initialized.");
}

void TinyUI::update(){
    tiny_handler.update();   
}

void TinyUI::render(){
    tiny_handler.render();
}

void TinyUI::free(TinyInterface* interface){
    tiny_handler.free(interface);
}

void TinyUI::clean_up(){
    if(tiny_handler.free_all() < 0){
        Logger::print(Logger::ERROR, "Failed to free all interfaces");
    }
}

TinyInterface* TinyUI::create_interface(Vector position, Vector size){
    if(!renderer){
        Logger::print(Logger::ERROR, "Failed to create a new interface");
        Logger::print(Logger::ERROR, "Renderer is nullptr");
        return nullptr;
    }

    TinyInterface* interface = new TinyInterface();
    interface->init(renderer, position, size);

    if(add_interface(interface) == -1){
        free(interface);
        Logger::print(Logger::ERROR, "Failed to create a new interface");
        return nullptr;
    }

    Logger::print(Logger::SUCCESS, "Tiny Interface (ID:", interface->id, ") was initialized.");
    return interface;
}

int TinyUI::add_interface(TinyInterface* interface){
    return tiny_handler.add(interface);
}

int TinyUI::remove_interface(TinyInterface* interface){
    return tiny_handler.remove(interface);
}

int TinyUI::contains_interface(TinyInterface* interface){
    return tiny_handler.contains(interface);
}

TinyInterface* TinyUI::get_interface(size_t id){
    TinyInterface* interface = tiny_handler.get(id);
    if(!interface) Logger::print(Logger::ERROR, "Failed to get interface by id");
    return interface;
}