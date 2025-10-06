#include "gfx/ui/button.hpp"
#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"

#include <iostream>

namespace gfx {
namespace ui {

Button::Button( const core::Vector2f& pos, const core::Vector2f& size )
    : Widget( pos, size ), background_( size )
{
}

void
Button::setSize( const core::Vector2f& size )
{
    size_ = size;
    background_.setSize( size );
}

void
Button::setRelPos( const core::Vector2f& pos )
{
    setPosition( pos );
    label_.moveInCenterOfRect( background_.getPosition(), background_.getSize() );
}

void
Button::setLabelFont( const core::Font& font, size_t size )
{
    label_.setFont( font );
    label_.setCharacterSize( size );
}

void
Button::setLabelText( const std::string& text )
{
    label_.setString( text );
}

void
Button::setBackgroundColor( const core::Color& color )
{
    background_.setFillColor( color );
}

void
Button::setPressed( bool pressed )
{
    pressed_ = pressed;
    updateVisuals();
}

void
Button::setHovered( bool hovered )
{
    hovered_ = hovered;
    updateVisuals();
}

void
Button::handleEvent( const core::Event& event )
{
    pressed_ = false;

    switch ( event.type )
    {
        case core::Event::MouseButtonPressed:
            onMousePress( event );
            break;
        case core::Event::MouseButtonReleased:
            onMouseRelease( event );
            break;
        case core::Event::MouseMoved:
            onMouseMove( event );
            break;
        case core::Event::Idle:
            onIdle( event );
            break;
        default:
            break;
    };
}

void
Button::onMousePress( const core::Event& event )
{
    core::Vector2f mouse( event.mouse_button.x, event.mouse_button.y );
    if ( pointInside( mouse ) )
    {
        pressed_ = true;
    }
}

void
Button::onMouseRelease( const core::Event& event )
{
    pressed_ = false;
}

void
Button::onMouseMove( const core::Event& event )
{
    core::Vector2f mouse( event.mouse_move.x, event.mouse_move.y );
    bool           was_hovered = hovered_;
    hovered_                   = pointInside( mouse );
    if ( was_hovered != hovered_ )
    {
        updateVisuals();
    }
}

void
Button::onIdle( const core::Event& event )
{
    core::Vector2i mouse_pos   = core::Mouse::getPosition();
    bool           was_hovered = hovered_;
    hovered_ =
        pointInside( { static_cast<float>( mouse_pos.x ), static_cast<float>( mouse_pos.y ) } );
    if ( was_hovered != hovered_ )
    {
        updateVisuals();
    }
}

void
Button::updateVisuals()
{
    if ( pressed_ )
    {
        background_.setFillColor( core::Color{ 100, 100, 255 } );
    } else if ( hovered_ )
    {
        background_.setFillColor( core::Color{ 150, 150, 255 } );
    } else
    {
        background_.setFillColor( core::Color::Blue );
    }
}

bool
Button::isPressed() const
{
    return pressed_;
}

bool
Button::isHovered() const
{
    return hovered_;
}

void
Button::drawSelf( core::Window& window, core::Transform transform ) const
{
    window.draw( background_, transform );
    window.draw( label_, transform );
}

} // namespace ui
} // namespace gfx
