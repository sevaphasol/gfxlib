#include "gfx/core/drawable.hpp"
#include "gfx/core/keyboard.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/window.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace gfx {
namespace core {

namespace detail {

extern Mouse::Button
fromSFML( sf::Mouse::Button button );

extern Keyboard::Key
fromSFML( sf::Keyboard::Key key );

extern sf::PrimitiveType
toSFML( PrimitiveType type );

} // namespace detail

class Window::Impl {
  public:
    sf::RenderWindow window;

    Impl( unsigned int width, unsigned int height, const char* title )
        : window( sf::VideoMode( width, height ), title )
    {
    }

    Impl() = default;
};

void*
Window::getImpl()
{
    return &impl_->window;
}

const void*
Window::getImpl() const
{
    return &impl_->window;
}

Window::Window( unsigned int width, unsigned int height, const char* title )
    : impl_( std::make_unique<Impl>( width, height, title ) )
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
Window::setFramerateLimit( unsigned int limit )
{
    impl_->window.setFramerateLimit( limit );
}

void
Window::draw( const Drawable& drawable, Transform transform )
{
    drawable.draw( *this, transform );
}

void
Window::draw( const Vertex*    vertices,
              std::size_t      vertex_count,
              PrimitiveType    type,
              const Transform& transform )
{
    const auto* sf_vertices  = reinterpret_cast<const sf::Vertex*>( vertices );
    const auto* sf_transform = static_cast<const sf::Transform*>( transform.getImpl() );
    auto        sf_type      = detail::toSFML( type );

    impl_->window.draw( sf_vertices, vertex_count, sf_type, *sf_transform );
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
            case sf::Event::TextEntered:
                event.type         = Event::TextEntered;
                event.text.unicode = sf_event.text.unicode;
                break;
            case sf::Event::KeyPressed:
                event.type     = Event::KeyPressed;
                event.key.code = detail::fromSFML( sf_event.key.code );
                break;
            case sf::Event::KeyReleased:
                event.type     = Event::KeyReleased;
                event.key.code = detail::fromSFML( sf_event.key.code );
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

} // namespace core
} // namespace gfx
