#pragma once

#include "gfx/core/mouse.hpp"
#include "gfx/core/keyboard.hpp"
#include <cstdint>

namespace gfx {
namespace core {

class Event {
  public:
    struct TextEvent
    {
        uint32_t unicode;
    };

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
        TextEntered,
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
        TextEvent        text;
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
