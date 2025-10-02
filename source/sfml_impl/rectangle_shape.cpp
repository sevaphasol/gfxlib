#include "rectangle_shape.hpp"
#include "transform.hpp"
#include "vector2.hpp"
#include "window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace gfx_core {

class RectangleShape::Impl {
  public:
    sf::RectangleShape rectangle_shape;

    explicit Impl( const Vector2f& size = Vector2f( 0, 0 ) )
    {
        sf::Vector2f sf_vector( size.x, size.y );
        rectangle_shape.setSize( sf_vector );
    }

    Impl() = default;
};

RectangleShape::~RectangleShape() = default;

RectangleShape::RectangleShape( const Vector2f& size ) : impl_( std::make_unique<Impl>( size ) ) {}

void
RectangleShape::setSize( const Vector2f& size )
{
    sf::Vector2f sf_vector( size.x, size.y );
    impl_->rectangle_shape.setSize( sf_vector );
}

void
RectangleShape::setFillColor( const gfx_core::Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->rectangle_shape.setFillColor( sf_color );
}

void
RectangleShape::setPosition( float x, float y )
{
    impl_->rectangle_shape.setPosition( x, y );
}

void
RectangleShape::setPosition( const gfx_core::Vector2f& pos )
{
    sf::Vector2f sf_vector( pos.x, pos.y );

    impl_->rectangle_shape.setPosition( sf_vector );
}

Vector2f
RectangleShape::getPosition() const
{
    auto sf_vector = impl_->rectangle_shape.getPosition();

    return Vector2f( sf_vector.x, sf_vector.y );
}

void
RectangleShape::draw( Window& window, Transform transform ) const
{
    auto* sf_window    = static_cast<sf::RenderWindow*>( window.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( transform.getImpl() );

    sf_window->draw( impl_->rectangle_shape, *sf_transform );
}

} // namespace gfx_core
