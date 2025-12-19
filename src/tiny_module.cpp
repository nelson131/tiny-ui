#include "../include/tiny_module.h"

namespace TinyModule {

    // Base struct -> 

    Base::Base(){};
    Base::~Base() = default;

    void Base::init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size){};
    void Base::update(){};
    void Base::render(){};

    int Base::load_rects(Vector* size){
        float x = 0, y = 0;
        if(size){
            x = this->size.x;
            y = this->size.y;
        } else {
            x = (*size).x;
            y = (*size).y;
        }

        if(x < 0 || y < 0){
            return -1;
        }

        dest_rect.w = x;
        dest_rect.h = y;
        src_rect.w = dest_rect.w;
        src_rect.h = dest_rect.h;
        return 0;
    }

    // Image module ->

    void Image::init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size){
        this->renderer = renderer;
        this->relative_inf = relative_inf;
        this->relative_position = &relative_inf->position;
        this->local_position = position;
        this->size = size;

        if((*relative_position).x + local_position.x > size.x || (*relative_position).y + local_position.y > size.y){
            Logger::print(Logger::ERROR, "Failed to init image module cause the position is beyond the size limits");
            return;
        }

        texture = TinyTexture::load(texture_path, renderer);
        if(load_rects(nullptr) == -1){
            Logger::print(Logger::ERROR, "Failed to load rects in image module");
        }
    }

    void Image::update(){
        global_position.x = (*relative_position).x + local_position.x;
        global_position.y = (*relative_position).y + local_position.y;

        dest_rect.x = global_position.x;
        dest_rect.y = global_position.y;
    }

    void Image::render(){
        SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);      
    }
};