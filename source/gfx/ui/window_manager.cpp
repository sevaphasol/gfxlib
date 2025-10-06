#include "gfx/core/event.hpp"
#include "gfx/ui/window_manager.hpp"

namespace gfx {
namespace ui {

WindowManager::WindowManager( float w, float h, const char* title )
    : window_( w, h, title ), desktop_( 0, 0, w, h ), renderer_( window_ )
{
    setFramerateLimit( 60 );
}

void
WindowManager::run()
{
    while ( window_.isOpen() )
    {
        handleEvents();
        draw();
    }
}

void
WindowManager::setFramerateLimit( float fps_limit )
{
    window_.setFramerateLimit( fps_limit );
}

void
WindowManager::setDeltaTime( float delta_time )
{
    delta_time_ = delta_time;
}

void
WindowManager::handleEvents()
{
    core::Event event;
    bool        has_events = false;
    while ( window_.pollEvent( event ) )
    {
        has_events = true;
        if ( event.type == core::Event::Closed )
        {
            window_.close();
        }

        renderer_.handleEvent( event, desktop_ );
    }

    if ( !has_events )
    {
        core::Event idle_event = core::Event::generateIdleEvent( delta_time_ );

        renderer_.handleEvent( idle_event, desktop_ );
    }
}

void
WindowManager::draw()
{
    window_.clear();
    renderer_.render( desktop_ );
    window_.display();
}

} // namespace ui
} // namespace gfx
