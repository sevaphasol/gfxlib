#pragma once

#include "mouse.hpp"

namespace gfx_core {

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

    enum Type { Closed, MouseButtonPressed, MouseButtonReleased, MouseMoved, Unknown };

    Type type;

    union {
        MouseMoveEvent   mouse_move;
        MouseButtonEvent mouse_button;
    };

    Event() : type( Unknown ) {}
};

} // namespace gfx_core
