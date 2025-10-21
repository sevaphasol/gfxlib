#pragma once

#include "gfx/core/mouse.hpp"
#include "gfx/core/keyboard.hpp"

namespace gfx {
namespace core {

class Event {
  public:
    struct KeyEvent
    {
        Keyboard::Key code;
    };

    struct MouseMoveEvent
    {
        int x;
        int y;
    };

    struct MouseButtonEvent
    {
        Mouse::Button button;
        int           x;
        int           y;
    };

    struct IdleEvent
    {
        float delta_time;
    };

    enum Type {
        Closed,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        Idle,
        Unknown
    };

    Type type;

    union {
        KeyEvent         key;
        MouseMoveEvent   mouse_move;
        MouseButtonEvent mouse_button;
        IdleEvent        idle;
    };

    static Event::IdleEvent
    generateIdleEvent( float delta_time )
    {
        return { delta_time };
    }

    Event() : type( Unknown ) {}
};

} // namespace core
} // namespace gfx
