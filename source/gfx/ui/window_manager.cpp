#include "gfx/core/event.hpp"
#include "gfx/ui/window_manager.hpp"

namespace gfx {
namespace ui {

WindowManager::WindowManager( float w, float h, const char* title )
    : window_( w, h, title ), desktop_( 0, 0, w, h )
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
WindowManager::setBackgroundColor( const gfx::core::Color& color )
{
    background_color_ = color;
}

void
WindowManager::addWidget( std::unique_ptr<gfx::ui::Widget> widget )
{
    desktop_.addChild( std::move( widget ) );
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
    while ( window_.pollEvent( event ) )
    {
        switch ( event.type )
        {
            case core::Event::Closed:
                window_.close();
                break;
            case core::Event::MouseButtonPressed:
                desktop_.onMousePress( event.mouse_button );
                break;
            case core::Event::MouseButtonReleased:
                desktop_.onMouseRelease( event.mouse_button );
                break;
            case core::Event::MouseMoved:
                desktop_.onMouseMove( event.mouse_move );
                break;
            default:
                break;
        }
    }

    desktop_.onIdle( core::Event::generateIdleEvent( delta_time_ ) );
}

void
WindowManager::draw()
{
    window_.clear( background_color_ );
    window_.draw( desktop_ );
    window_.display();
}

} // namespace ui
} // namespace gfx
