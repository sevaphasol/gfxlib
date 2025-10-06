#include "gfx/core/circle_shape.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/window.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace gfx {
namespace core {

class CircleShape::Impl {
  public:
    sf::CircleShape circle_shape;

    explicit Impl( float radius ) : circle_shape( radius ) { circle_shape.setScale( { 1, 1 } ); }

    Impl() = default;
};

CircleShape::~CircleShape() = default;

CircleShape::CircleShape( float radius ) : impl_( std::make_unique<Impl>( radius ) ) {}

CircleShape::CircleShape( const CircleShape& other )
    : impl_( std::make_unique<Impl>( *other.impl_ ) )
{
}

void
CircleShape::setRadius( float radius )
{
    impl_->circle_shape.setRadius( radius );
}

float
CircleShape::getRadius() const
{
    return impl_->circle_shape.getRadius();
}

void
CircleShape::setFillColor( const Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->circle_shape.setFillColor( sf_color );
}

void
CircleShape::setOutlineThickness( float thickness )
{
    impl_->circle_shape.setOutlineThickness( thickness );
}

void
CircleShape::setOutlineColor( const Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->circle_shape.setOutlineColor( sf_color );
}

void
CircleShape::draw( Window& window, Transform transform ) const
{
    Transform local_transform = transform.combine( getTransform() );

    auto* sf_window    = static_cast<sf::RenderWindow*>( window.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( local_transform.getImpl() );

    sf_window->draw( impl_->circle_shape, *sf_transform );
}

} // namespace core
} // namespace gfx
