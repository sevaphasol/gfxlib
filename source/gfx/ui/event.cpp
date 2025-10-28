#include "gfx/ui/event.hpp"
#include "gfx/ui/widget.hpp"

namespace gfx {
namespace ui {

bool
IdleEvent::apply( Widget* widget ) const
{
    return widget->onIdle( *this );
}

bool
KeyPressEvent::apply( Widget* widget ) const
{
    return widget->onKeyPress( *this );
}

bool
KeyReleaseEvent::apply( Widget* widget ) const
{
    return widget->onKeyRelease( *this );
}

bool
MousePressEvent::apply( Widget* widget ) const
{
    return widget->onMousePress( *this );
}

bool
MouseReleaseEvent::apply( Widget* widget ) const
{
    return widget->onMouseRelease( *this );
}

bool
MouseMoveEvent::apply( Widget* widget ) const
{
    return widget->onMouseMove( *this );
}

} // namespace ui
} // namespace gfx
