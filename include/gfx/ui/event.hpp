#pragma once

#include "gfx/core/event.hpp"
namespace gfx {
namespace ui {

class Widget;

struct Event
{
    Event( const core::Event& info ) : info( info ) {}

    core::Event info;

    virtual bool
    apply( Widget* widget ) const = 0;
};

// clang-format off
struct IdleEvent         : public Event { IdleEvent         (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct TextEnteredEvent  : public Event { TextEnteredEvent  (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct KeyPressEvent     : public Event { KeyPressEvent     (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct KeyReleaseEvent   : public Event { KeyReleaseEvent   (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct MousePressEvent   : public Event { MousePressEvent   (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct MouseReleaseEvent : public Event { MouseReleaseEvent (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
struct MouseMoveEvent    : public Event { MouseMoveEvent    (const core::Event& info) : Event(info) {} bool apply( Widget* widget ) const override final; };
//clang-format on

} // namespace ui
} // namespace gfx
