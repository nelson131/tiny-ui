#ifndef TINY_EVENT_H
#define TINY_EVENT_H

#include "tiny_vector.h"
#include "tiny_logger.h"
#include <SDL2/SDL.h>

// Event class
// Keeps events structs, types and handles events logics

using callback = void(*)();

enum class EventType {
    CREATE_EVENT,
    DESTROY_EVENT,
    ENABLE_EVENT,
    DISABLE_EVENT,
    MOVE_GLOBAL_EVENT,
    MOVE_LOCAL_EVENT,
    CURSOR_IN_AREA_EVENT,
    CURSOR_ENTER_EVENT,
    CURSOR_LEAVE_EVENT,
    CLICK_EVENT
};

namespace TinyEvent {

    struct Base {
        Base(callback func);
        ~Base();

        SDL_Event event;
        callback func = nullptr;

        virtual void handle();

        void load_func(callback func);
    };

    struct BaseMouse {
        BaseMouse();
        BaseMouse(const Vector& relative_pos, const Vector& relative_size);
        ~BaseMouse();

        const Vector& relative_pos = {0, 0};
        const Vector& relative_size = {0, 0};
        int x, y;

        void update();
        bool in_area();
    };

    struct onCreate : Base {
        onCreate(callback func);
        ~onCreate();
    };

    struct onDestroy : Base {
        onDestroy(callback func);
        ~onDestroy();
    };

    struct onEnable : Base {
        onEnable(callback func, const bool& is_visible);
        ~onEnable();

        const bool& is_visible;

        void handle() override;

        bool was_visible = false;
    };

    struct onDisable : Base {
        onDisable(callback func, const bool& is_visible);
        ~onDisable();

        const bool& is_visible;

        void handle() override;

        bool was_visible = false;
    };

    struct onMove : Base {
        onMove(callback func, const Vector& position);
        ~onMove();

        const Vector& relative_pos;
        float x, y;

        void handle() override;
    };

    struct onCursorInArea : Base, BaseMouse {
        onCursorInArea(callback func, const Vector& position, const Vector& size);
        ~onCursorInArea();

        void handle() override;
    };

    struct onCursorEnter : Base, BaseMouse {
        onCursorEnter(callback func, const Vector& position, const Vector& size);
        ~onCursorEnter();

        void handle() override;

        bool was_inside = true;
    };

    struct onCursorLeave : Base, BaseMouse {
        onCursorLeave(callback func, const Vector& position, const Vector& size);
        ~onCursorLeave();

        void handle() override;

        bool was_inside = false;
    };

    struct onClick : Base, BaseMouse {
        onClick(callback func, const Vector& position, const Vector& size);
        ~onClick();

        void handle() override;

        bool was_pressed = false;
    };

};

#endif