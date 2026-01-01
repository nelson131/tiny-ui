#include "../include/tiny_module.h"
#include "../include/tiny_interface.h"

namespace TinyModule {

    // Base struct
    // Basis of modules, inherited in other modules

    Base::Base(Vector pos, Vector size)
        : local_position(pos), size(size)
    {};
    Base::~Base(){
        if(event) delete event;
    }

    int Base::init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id){ return 0; };
    void Base::update(){};
    void Base::render(){};

    int Base::setup(SDL_Renderer* renderer, TinyInterface* relative_inf, std::string module_name, size_t id){
        if(!renderer){
            Logger::print(Logger::ERROR, "Failed to init ", module_name, " module cause the renderer is nullptr");
            return -1;
        }
        if(!relative_inf){
            Logger::print(Logger::ERROR, "Failed to init ", module_name, " module cause the relative interface is nullptr");
            return -1;
        }
        this->renderer = renderer;
        this->relative_inf = relative_inf;
        this->relative_position = &relative_inf->position;
        this->id = id;

        if(size.x > relative_inf->size.x || size.y > relative_inf->size.y){
            Logger::print(Logger::ERROR, "Failed to init ", module_name, " module cause the position is beyond the size limits");
            return -1;
        }

        if(load_rects(nullptr) < 0){
            Logger::print(Logger::ERROR, "Failed to load rects in ", module_name, " module");
            return -1;
        }

        return 0;
    }

    int Base::load_rects(Vector* size){
        float x = 0, y = 0;
        if(!size){
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

    void Base::set_executor(EventType event_type, callback func){
        if(!func){
            Logger::print(Logger::ERROR, "Failed to set executor, cause func is nullptr");
            return;
        }

        if(event){
            delete event;
            event = nullptr;
        }

        switch (event_type) {
        case EventType::CREATE_EVENT:
            event = new TinyEvent::onCreate();
            break;
        case EventType::DESTROY_EVENT:
            event = new TinyEvent::onDestroy();
            break;
        case EventType::ENABLE_EVENT:
            event = new TinyEvent::onEnable();
            break;
        case EventType::DISABLE_EVENT:
            event = new TinyEvent::onDisable();
            break;
        case EventType::MOVE_EVENT:
            event = new TinyEvent::onMove();
            break;
        case EventType::CURSOR_ENTER_EVENT:
            event = new TinyEvent::onCursorEnter();
            break;
        case EventType::CURSOR_LEAVE_EVENT:
            event = new TinyEvent::onCursorLeave();
            break;
        case EventType::CLICK_EVENT:
            event = new TinyEvent::onClick();
            break;
        default:
            break;
        }
    }

    // Image module
    // Handles loading and rendering a texture image on the screen

    Image::Image(std::string texture_path, Vector position, Vector size, bool stretch)
        : Base(position, size),
        texture_path(texture_path), stretch(stretch)
    {}

    Image::~Image(){
        if(texture){
            SDL_DestroyTexture(texture);
        }
    }

    int Image::init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id){
        if(setup(renderer, relative_inf, "Image", id) < 0){
            Logger::print(Logger::ERROR, "Failed to setup image module");
            return -1;
        }
        if(stretch){
            texture = TinyTexture::load(texture_path, renderer, src_rect.w, src_rect.h);
        } else {
            texture = TinyTexture::load(texture_path, renderer);
        }

        return 0;
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

    Text::Text(std::string font_path, std::string content, Vector position, Vector size)
        : Base(position, size), 
        font_path(font_path), content(content)
    {}

    Text::~Text(){
        text.clear();
    }

    int Text::init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id){
        if(setup(renderer, relative_inf, "Text", id) < 0){
            Logger::print(Logger::ERROR, "Failed to setup text module");
            return -1;
        }

        text.create(renderer, font_path.c_str(), content);

        return 0;
    }

    void Text::update(){
        global_position.x = (*relative_position).x + local_position.x;
        global_position.y = (*relative_position).y + local_position.y;

        dest_rect.x = global_position.x;
        dest_rect.y = global_position.y;
        text.update(dest_rect);
    }

    void Text::render(){
        text.render();
    }
};