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

BaseMouse::~BaseMouse(){}

void BaseMouse::update(){
    SDL_GetMouseState(&x, &y);
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

onEnable::onEnable(callback func)
    : Base(func)
{}

onEnable::~onEnable(){}

// DISABLE_EVENT >>>

onDisable::onDisable(callback func)
    : Base(func)
{}

onDisable::~onDisable(){}

// MOVE_EVENT >>>

onMove::onMove(callback func)
    : Base(func)
{}

onMove::~onMove(){}

// CURSOR_ENTER_EVENT >>>

onCursorEnter::onCursorEnter(callback func)
    : Base(func)
{}

onCursorEnter::~onCursorEnter(){}

// CURSOR_LEAVE_EVENT >>>

onCursorLeave::onCursorLeave(callback func)
    : Base(func)
{}

onCursorLeave::~onCursorLeave(){}

// CLICK_EVENT >>>

onClick::onClick(callback func, const Vector& position, const Vector& size)
    : Base(func),
    relative_pos(position), relative_size(size)
{}

onClick::~onClick(){}

void onClick::handle(){
    if(!func){
        Logger::print(Logger::ERROR, "Failed to handle click event cause func is nullptr");
    }

    Uint32 mouse_state = SDL_GetMouseState(&x, &y);

    if(mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT) && in_area()){
        (*func)();
    }
}

bool onClick::in_area(){
    return x >= relative_pos.x &&
        x <= relative_pos.x + relative_size.x &&
        y >= relative_pos.y &&
        y <= relative_pos.y + relative_size.y;
}