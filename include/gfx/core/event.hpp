#pragma once

#include "gfx/core/mouse.hpp"

namespace gfx {
namespace core {

class Event {
  public:
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

    enum Type { Closed, MouseButtonPressed, MouseButtonReleased, MouseMoved, Idle, Unknown };

    Type type;

    union {
        MouseMoveEvent   mouse_move;
        MouseButtonEvent mouse_button;
        IdleEvent        idle;
    };

    static Event
    generateIdleEvent( float delta_time )
    {
        Event idle_event = {};

        idle_event.type            = Type::Idle;
        idle_event.idle.delta_time = delta_time;

        return idle_event;
    }

    Event() : type( Unknown ) {}
};

} // namespace core
} // namespace gfx
