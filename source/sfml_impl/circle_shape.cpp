#include "circle_shape.hpp"
#include "window.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace gfx_core {

class CircleShape::Impl {
  public:
    sf::CircleShape circle_shape;

    explicit Impl( float radius ) : circle_shape( radius ) {}

    Impl() = default;
};

void*
CircleShape::getCircleShapeImpl() const
{
    return &impl_->circle_shape;
}

CircleShape::CircleShape( float radius ) : impl_( std::make_unique<Impl>( radius ) ) {}

CircleShape::~CircleShape() = default;

void
CircleShape::setRadius( float radius )
{
    impl_->circle_shape.setRadius( radius );
}

void
CircleShape::setFillColor( const gfx_core::Color& color )
{
    sf::Color sf_color( color.r, color.g, color.b, color.a );

    impl_->circle_shape.setFillColor( sf_color );
}

void
CircleShape::setPosition( float x, float y )
{
    impl_->circle_shape.setPosition( x, y );
}

void
CircleShape::setPosition( const gfx_core::Vector2f& pos )
{
    sf::Vector2f sf_vector( pos.x, pos.y );

    impl_->circle_shape.setPosition( sf_vector );
}

void
CircleShape::draw( Window& window ) const
{
    auto* sf_window = static_cast<sf::RenderWindow*>( window.getWindowImpl() );

    sf_window->draw( impl_->circle_shape );
}

} // namespace gfx_core
