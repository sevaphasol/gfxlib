#include "drawable.hpp"
#include "vector2.hpp"
#include "window.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace gfx_core {

namespace detail {

extern Mouse::Button
fromSFML( sf::Mouse::Button button );

}

namespace impl {

class Window {
  public:
    sf::RenderWindow window;

    Window( unsigned int width, unsigned int height, const char* title )
        : window( sf::VideoMode( width, height ), title )
    {
    }

    Window() = default;
};

} // namespace impl

void*
Window::getWindowImpl() const
{
    return &impl_->window;
}

Window::Window( unsigned int width, unsigned int height, const char* title )
    : impl_( std::make_unique<impl::Window>( width, height, title ) )
{
}

Window::~Window() = default;

void
Window::close()
{
    impl_->window.close();
}

bool
Window::isOpen() const
{
    return impl_->window.isOpen();
}

Vector2u
Window::getSize() const
{
    sf::Vector2u sf_vector = impl_->window.getSize();
    return Vector2u( sf_vector.x, sf_vector.y );
}

void
Window::clear( const Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );
    impl_->window.clear( sf_color );
}

void
Window::display()
{
    impl_->window.display();
}

void
Window::draw( const Drawable& drawable )
{
    drawable.draw( *this );
}

bool
Window::pollEvent( Event& event )
{
    sf::Event sf_event;

    if ( impl_->window.pollEvent( sf_event ) )
    {
        switch ( sf_event.type )
        {
            case sf::Event::Closed:
                event.type = Event::Closed;
                break;
            case sf::Event::MouseButtonPressed:
                event.type                = Event::MouseButtonPressed;
                event.mouse_button.button = detail::fromSFML( sf_event.mouseButton.button );
                event.mouse_button.x      = sf_event.mouseButton.x;
                event.mouse_button.y      = sf_event.mouseButton.y;
                break;
            case sf::Event::MouseButtonReleased:
                event.type                = Event::MouseButtonReleased;
                event.mouse_button.button = detail::fromSFML( sf_event.mouseButton.button );
                event.mouse_button.x      = sf_event.mouseButton.x;
                event.mouse_button.y      = sf_event.mouseButton.y;
                break;
            case sf::Event::MouseMoved:
                event.type         = Event::MouseMoved;
                event.mouse_move.x = sf_event.mouseMove.x;
                event.mouse_move.y = sf_event.mouseMove.y;
                break;
            default:
                event.type = Event::Unknown;
                break;
        }

        return true;
    }

    return false;
}

} // namespace gfx_core
