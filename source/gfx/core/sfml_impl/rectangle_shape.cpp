#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace gfx {
namespace core {

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

RectangleShape::RectangleShape( const RectangleShape& other )
    : impl_( std::make_unique<Impl>( *other.impl_ ) )
{
}

void
RectangleShape::setSize( float w, float h )
{
    sf::Vector2f sf_vector( w, h );
    impl_->rectangle_shape.setSize( sf_vector );
}

void
RectangleShape::setSize( const core::Vector2f& size )
{
    sf::Vector2f sf_vector( size.x, size.y );
    impl_->rectangle_shape.setSize( sf_vector );
}

Vector2f
RectangleShape::getSize() const
{
    auto sf_size = impl_->rectangle_shape.getSize();

    return Vector2f( sf_size.x, sf_size.y );
}

void
RectangleShape::setFillColor( const Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->rectangle_shape.setFillColor( sf_color );
}

void
RectangleShape::setOutlineThickness( float thickness )
{
    impl_->rectangle_shape.setOutlineThickness( thickness );
}

void
RectangleShape::setOutlineColor( const Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->rectangle_shape.setOutlineColor( sf_color );
}

void
RectangleShape::draw( Window& window, Transform transform ) const
{
    Transform local_transform = transform.combine( getTransform() );

    auto* sf_window    = static_cast<sf::RenderWindow*>( window.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( local_transform.getImpl() );

    sf_window->draw( impl_->rectangle_shape, *sf_transform );
}

} // namespace core
} // namespace gfx
