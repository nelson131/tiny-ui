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

TinyInterface* TinyUI::create_interface(Vector position, Vector size){
    if(!renderer){
        Logger::print(Logger::ERROR, "Failed to create a new interface");
        Logger::print(Logger::ERROR, "Renderer is nullptr");
        return nullptr;
    }

    TinyInterface* interface = new TinyInterface();
    interface->init(renderer, position, size);

    if(tiny_handler.add(interface) < 0){
        delete interface;
        Logger::print(Logger::ERROR, "Failed to create a new interface");
        return nullptr;
    }

    Logger::print(Logger::SUCCESS, "Tiny Interface (ID:", interface->id, ") was initialized.");
    return interface;
}

int TinyUI::delete_interface(TinyInterface* interface){
    if(!interface){
        Logger::print(Logger::ERROR, "Failed to delete interface: nullptr");
        return -1;
    }
    if(tiny_handler.remove(interface) < 0){
        Logger::print(Logger::ERROR, "Failed to delete interface (ID:", interface->id, ")");
        return -1;
    }
    return 0;
}

int TinyUI::delete_interface_by_id(size_t id){
    if(tiny_handler.remove_by_id(id) < 0){
        Logger::print(Logger::ERROR, "Failed to delete interface (ID:", id, ") by id");
        return -1;
    }
    return 0;
}

int TinyUI::contains_interface(TinyInterface* interface){
    return tiny_handler.contains(interface);
}

TinyInterface* TinyUI::get_interface(size_t id){
    TinyInterface* interface = tiny_handler.get(id);
    if(!interface) Logger::print(Logger::ERROR, "Failed to get interface by id");
    return interface;
}

void TinyUI::clean_up(){
    tiny_handler.remove_all();
}