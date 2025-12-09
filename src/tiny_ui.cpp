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