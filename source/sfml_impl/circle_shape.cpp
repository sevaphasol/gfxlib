#include "gfx_core/circle_shape.hpp"
#include "gfx_core/transform.hpp"
#include "gfx_core/window.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace gfx_core {

class CircleShape::Impl {
  public:
    sf::CircleShape circle_shape;

    explicit Impl( float radius ) : circle_shape( radius ) { circle_shape.setScale( { 1, 1 } ); }

    Impl() = default;
};

CircleShape::~CircleShape() = default;

CircleShape::CircleShape( float radius ) : impl_( std::make_unique<Impl>( radius ) ) {}

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
CircleShape::setFillColor( const gfx_core::Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->circle_shape.setFillColor( sf_color );
}

void
CircleShape::draw( Window& window, Transform transform ) const
{
    Transform local_transform = transform.combine( getTransform() );

    auto* sf_window    = static_cast<sf::RenderWindow*>( window.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( local_transform.getImpl() );

    sf_window->draw( impl_->circle_shape, *sf_transform );
}

} // namespace gfx_core
