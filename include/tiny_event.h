#ifndef TINY_EVENT_H
#define TINY_EVENT_H

#include "tiny_vector.h"
#include "tiny_logger.h"
#include <SDL2/SDL.h>

using callback = void(*)();

enum class EventType {
    CREATE_EVENT,
    DESTROY_EVENT,
    ENABLE_EVENT,
    DISABLE_EVENT,
    MOVE_EVENT,
    CURSOR_ENTER_EVENT,
    CURSOR_LEAVE_EVENT,
    CLICK_EVENT
};

namespace TinyEvent {

    struct Base {
        Base(callback func);
        ~Base();

        callback func = nullptr;

        virtual void handle();

        void load_func(callback func);
    };

    struct BaseMouse {
        BaseMouse();
        ~BaseMouse();

        int x, y;

        void update();
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
        onEnable(callback func);
        ~onEnable();
    };

    struct onDisable : Base {
        onDisable(callback func);
        ~onDisable();
    };

    struct onMove : Base {
        onMove(callback func);
        ~onMove();
    };

    struct onCursorEnter : Base, BaseMouse {
        onCursorEnter(callback func);
        ~onCursorEnter();
    };

    struct onCursorLeave : Base, BaseMouse {
        onCursorLeave(callback func);
        ~onCursorLeave();
    };

    struct onClick : Base, BaseMouse {
        onClick(callback func, const Vector& position, const Vector& size);
        ~onClick();

        const Vector& relative_pos;
        const Vector& relative_size;

        void handle() override;

        bool in_area();
    };

};

#endif