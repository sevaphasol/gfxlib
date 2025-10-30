#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/mouse.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"
#include <cstdio>
#include "gfx/ui/button.hpp"
#include <iostream>

namespace gfx {
namespace ui {

Button::Button( const gfx::core::Vector2f& pos,
                const gfx::core::Vector2f& size,
                const gfx::core::Color&    default_color,
                const gfx::core::Color&    hovered_color,
                const gfx::core::Color&    pressed_color,
                const gfx::core::Font&     font,
                const std::string&         title,
                const gfx::core::Color&    font_color,
                size_t                     font_size )
    : Widget( pos, size ),
      background_( size ),
      label_( title, font, font_size ),
      default_color_( default_color ),
      hovered_color_( hovered_color ),
      pressed_color_( pressed_color )
{
    background_.setFillColor( default_color );
    label_.setFillColor( font_color );
    label_.moveInCenterOfRect( size );
}

void
Button::setRelPos( const gfx::core::Vector2f& pos )
{
    setPosition( pos );
    label_.moveInCenterOfRect( size_ );
}

void
Button::setSize( const gfx::core::Vector2f& size )
{
    size_ = size;
    background_.setSize( size );
    label_.moveInCenterOfRect( size );
}

void
Button::setLabelText( const std::string& text )
{
    label_.setString( text );
}

void
Button::setLabelFont( const gfx::core::Font& font, size_t size )
{
    label_.setFont( font );
    label_.setCharacterSize( size );
}

void
Button::setBackgroundColor( const gfx::core::Color& color )
{
    background_.setFillColor( color );
}

bool
Button::isPressed() const
{
    return is_pressed_;
}

bool
Button::onIdle( const Event& event )
{
    updateVisuals();
    return false;
}

// bool
// Button::onMousePress( const Event& event )
// {
// if ( is_hovered_ && event.info.mouse_button.button == gfx::core::Mouse::Left )
// {
// is_pressed_ = true;
// updateVisuals();
// return true;
// }
//
// return false;
// }
//
// bool
// Button::onMouseRelease( const Event& event )
// {
// is_pressed_ = false;
// updateVisuals();
// return is_hovered_;
// }
//
// bool
// Button::onMouseMove( const Event& event )
// {
// // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
//
// is_hovered_ =
// pointInside( gfx::core::Vector2f( event.info.mouse_move.x, event.info.mouse_move.y ) );
//
// // // std::cerr << event.info.mouse_move.x << " " << event.info.mouse_move.y << std::endl;
// // // std::cerr << getPosition().x << " " << getPosition().y << std::endl;
// // // std::cerr << is_hovered_ << std::endl;
//
// if ( !is_hovered_ )
// {
// is_pressed_ = false;
// }
//
// updateVisuals();
//
// return is_hovered_;
// }

void
Button::updateVisuals()
{
    if ( is_pressed_ )
    {
        background_.setFillColor( pressed_color_ );
    } else if ( is_hovered_ )
    {
        background_.setFillColor( hovered_color_ );
    } else
    {
        background_.setFillColor( default_color_ );
    }
}

void
Button::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    core::Transform widget_transform = transform.combine( getTransform() );

    window.draw( background_, widget_transform );
    window.draw( label_, widget_transform );
}

} // namespace ui
} // namespace gfx
