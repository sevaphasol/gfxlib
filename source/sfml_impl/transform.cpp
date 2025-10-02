#include "transform.hpp"

#include <SFML/Graphics/Transform.hpp>

namespace gfx_core {

class Transform::Impl {
  public:
    sf::Transform transform;
};

void*
Transform::getImpl()
{
    return &impl_->transform;
}

Transform::~Transform() = default;

Transform::Transform() : impl_( std::make_unique<Impl>() ) {}

Transform::Transform( const Transform& other ) : impl_( std::make_unique<Impl>( *other.impl_ ) ) {}

const Transform&
Transform::operator=( const Transform& other )
{
    return other;
}

Transform&
Transform::translate( float x, float y )
{
    impl_->transform.translate( x, y );
    return *this;
}

Transform&
Transform::translate( const Vector2f& v )
{
    return translate( v.x, v.y );
}

Transform&
Transform::rotate( float angle_degrees )
{
    impl_->transform.rotate( angle_degrees );
    return *this;
}

Transform&
Transform::scale( float x, float y )
{
    impl_->transform.scale( x, y );
    return *this;
}

Transform&
Transform::scale( float factor )
{
    return scale( factor, factor );
}

Transform
Transform::combine( const Transform& other ) const
{
    Transform result;
    result.impl_->transform = impl_->transform * other.impl_->transform;

    return result;
}

} // namespace gfx_core
