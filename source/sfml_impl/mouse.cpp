#include "mouse.hpp"
#include "window.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace gfx_core {

namespace detail {

sf::Mouse::Button
toSFML( Mouse::Button button )
{
    switch ( button )
    {
        case Mouse::Left:
            return sf::Mouse::Left;
        case Mouse::Right:
            return sf::Mouse::Right;
        case Mouse::Middle:
            return sf::Mouse::Middle;
        case Mouse::XButton1:
            return sf::Mouse::XButton1;
        case Mouse::XButton2:
            return sf::Mouse::XButton2;
        default:
            return sf::Mouse::ButtonCount;
    }
}

Mouse::Button
fromSFML( sf::Mouse::Button button )
{
    switch ( button )
    {
        case sf::Mouse::Left:
            return Mouse::Left;
        case sf::Mouse::Right:
            return Mouse::Right;
        case sf::Mouse::Middle:
            return Mouse::Middle;
        case sf::Mouse::XButton1:
            return Mouse::XButton1;
        case sf::Mouse::XButton2:
            return Mouse::XButton2;
        default:
            return Mouse::ButtonCount;
    }
}

} // namespace detail

Vector2i
Mouse::getPosition()
{
    auto pos = sf::Mouse::getPosition();
    return Vector2i( pos.x, pos.y );
}

Vector2i
Mouse::getPosition( const Window& relative_to )
{
    const auto* sf_window = static_cast<const sf::RenderWindow*>( relative_to.getWindowImpl() );

    if ( sf_window == nullptr )
    {
        return Vector2i( 0, 0 );
    }

    auto pos = sf::Mouse::getPosition( *sf_window );
    return Vector2i( pos.x, pos.y );
}

void
Mouse::setPosition( const Vector2i& position )
{
    sf::Mouse::setPosition( sf::Vector2i( position.x, position.y ) );
}

void
Mouse::setPosition( const Vector2i& position, const Window& relative_to )
{
    const auto* sf_window = static_cast<const sf::RenderWindow*>( relative_to.getWindowImpl() );

    if ( sf_window != nullptr )
    {
        sf::Mouse::setPosition( sf::Vector2i( position.x, position.y ), *sf_window );
    }
}

bool
Mouse::isButtonPressed( Button button )
{
    return sf::Mouse::isButtonPressed( detail::toSFML( button ) );
}

} // namespace gfx_core
