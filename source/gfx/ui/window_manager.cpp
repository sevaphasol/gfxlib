#include "gfx/core/event.hpp"
#include "gfx/ui/event.hpp"
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
    core::Event core_event;
    while ( window_.pollEvent( core_event ) )
    {
        switch ( core_event.type )
        {
            case core::Event::Closed:
                window_.close();
                break;
            case core::Event::KeyPressed:
                ui::KeyPressEvent( core_event ).apply( &desktop_ );
                break;
            case core::Event::KeyReleased:
                ui::KeyReleaseEvent( core_event ).apply( &desktop_ );
                break;
            case core::Event::MouseButtonPressed:
                ui::MousePressEvent( core_event ).apply( &desktop_ );
                break;
            case core::Event::MouseButtonReleased:
                ui::MouseReleaseEvent( core_event ).apply( &desktop_ );
                break;
            case core::Event::MouseMoved:
                ui::MouseMoveEvent( core_event ).apply( &desktop_ );
                break;
            default:
                break;
        }
    }

    core_event.idle = core::Event::generateIdleEvent( delta_time_ );

    ui::IdleEvent( core_event ).apply( &desktop_ );
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
