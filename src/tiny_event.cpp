#include "../include/tiny_event.h"

using namespace TinyEvent;

// Base structs >>>

Base::Base(callback func)
    : func(func)
{}

Base::~Base(){}

void Base::handle(){};

void Base::load_func(callback func){
    this->func = func;
}

BaseMouse::BaseMouse()
    : x(0), y(0)
{}

BaseMouse::BaseMouse(const Vector& relative_pos, const Vector& relative_size)
    : x(0), y(0), 
    relative_pos(relative_pos), relative_size(relative_size)
{}

BaseMouse::~BaseMouse(){}

void BaseMouse::update(){
    SDL_GetMouseState(&x, &y);
}

bool BaseMouse::in_area(){
    return x >= relative_pos.x &&
        x <= relative_pos.x + relative_size.x &&
        y >= relative_pos.y &&
        y <= relative_pos.y + relative_size.y;
}

// CREATE_EVENT >>>

onCreate::onCreate(callback func)
    : Base(func)
{}

onCreate::~onCreate(){}

// DESTROY_EVENT >>

onDestroy::onDestroy(callback func)
    : Base(func)
{}

onDestroy::~onDestroy(){}

// ENABLE_EVENT >>>

onEnable::onEnable(callback func, const bool& is_visible)
    : Base(func),
    is_visible(is_visible), was_visible(is_visible)
{}

void onEnable::handle(){
    if(!was_visible && is_visible){
        (*func)();
        was_visible = true;
    }

    if(was_visible && !is_visible){
        was_visible = false;
    }
}

onEnable::~onEnable(){}

// DISABLE_EVENT >>>

onDisable::onDisable(callback func, const bool& is_visible)
    : Base(func),
    is_visible(is_visible), was_visible(is_visible)
{}

void onDisable::handle(){
    if(was_visible && !is_visible){
        (*func)();
        was_visible = false;
    }

    if(!was_visible && is_visible){
        was_visible = true;
    }
}

onDisable::~onDisable(){}

// MOVE_EVENT >>>

onMove::onMove(callback func, const Vector& position)
    : Base(func),
    relative_pos(position), x(position.x), y(position.y)
{}

void onMove::handle(){
    if(relative_pos.x != x || relative_pos.y != y){
        (*func)();
        x = relative_pos.x;
        y = relative_pos.y;
    }
}

onMove::~onMove(){}

// CURSOR_IN_AREA_EVENT >>>

onCursorInArea::onCursorInArea(callback func, const Vector& position, const Vector& size)
    : Base(func),
    BaseMouse(position, size)
{}

void onCursorInArea::handle(){
    if(in_area()){
        (*func)();
    }   
}

onCursorInArea::~onCursorInArea(){}

// CURSOR_ENTER_EVENT >>>

onCursorEnter::onCursorEnter(callback func, const Vector& position, const Vector& size)
    : Base(func),
    BaseMouse(position, size)
{}

void onCursorEnter::handle(){
    update();

    if(!was_inside && in_area()){
        was_inside = true;
        (*func)();
    }

    if(was_inside && !in_area()){
        was_inside = false;
    }
}

onCursorEnter::~onCursorEnter(){}

// CURSOR_LEAVE_EVENT >>>

onCursorLeave::onCursorLeave(callback func, const Vector& position, const Vector& size)
    : Base(func),
    BaseMouse(position, size)
{}

void onCursorLeave::handle(){
    update();

    if(was_inside && !in_area()){
        was_inside = false;
        (*func)();
    }

    if(!was_inside && in_area()){
        was_inside = true;
    }
}

onCursorLeave::~onCursorLeave(){}

// CLICK_EVENT >>>

onClick::onClick(callback func, const Vector& position, const Vector& size)
    : Base(func), 
    BaseMouse(position, size)
{}

void onClick::handle(){
    if(!func){
        Logger::print(Logger::ERROR, "Failed to handle click event cause func is nullptr");
    }

    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    bool pressed = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);

    if(pressed && !was_pressed && in_area()){
        (*func)();
    }

    was_pressed = pressed;
}

onClick::~onClick(){}
