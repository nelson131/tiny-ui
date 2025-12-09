#include "../include/tiny_module.h"

namespace TinyModule {

    // Base struct -> 

    Base::Base(){};
    Base::~Base() = default;

    void Base::init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size){};
    void Base::update(){};
    void Base::render(){};

    // Image module ->

    void Image::init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size){
        this->renderer = renderer;
        this->relative_inf = relative_inf;
        this->position = position;
        this->size = size;

        texture = TinyTexture::load(texture_path, renderer);
    }

    void Image::update(){

    }

    void Image::render(){
        
    }
};