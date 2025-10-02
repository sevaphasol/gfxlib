#include "transform.hpp"

#include <SFML/Graphics/Transform.hpp>
#include <cstdio>
#include <memory>

namespace gfx_core {

class Transform::Impl {
  public:
    Impl() = default;

    // clang-format off
	Impl(float a00, float a01, float a02,
         float a10, float a11, float a12,
         float a20, float a21, float a22) : transform(a00, a01, a02,
													  a10, a11, a12,
													  a20, a21, a22) {}
    // clang-format on

    sf::Transform transform;
};

void*
Transform::getImpl()
{
    return &impl_->transform;
}

Transform::~Transform() = default;

const Transform Transform::Identity = Transform();

Transform::Transform() : impl_( std::make_unique<Impl>() ) {}

// clang-format off
Transform::Transform(float a00, float a01, float a02,
                     float a10, float a11, float a12,
                     float a20, float a21, float a22)
    : impl_(std::make_unique<Impl>(a00, a01, a02,
								   a10, a11, a12,
								   a20, a21, a22))
{
}
// clang-format on

Transform::Transform( const Transform& other ) : impl_( std::make_unique<Impl>( *other.impl_ ) ) {}

Transform&
Transform::operator=( const Transform& other )
{
    if ( this != &other )
    {
        impl_ = std::make_unique<Impl>( *other.impl_ );
    }

    return *this;
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
Transform::rotate( float angle_degrees, float center_x, float center_y )
{
    impl_->transform.rotate( angle_degrees, center_x, center_y );

    return *this;
}

Transform&
Transform::rotate( float angle_degrees, const Vector2f& center )
{
    impl_->transform.rotate( angle_degrees, center.x, center.y );

    return *this;
}

Transform&
Transform::scale( float factor )
{
    impl_->transform.scale( factor, factor );
    return *this;
}

Transform&
Transform::scale( const Vector2f& factors )
{
    impl_->transform.scale( factors.x, factors.y );
    return *this;
}

Transform&
Transform::scale( float factor, const Vector2f& center )
{
    impl_->transform.scale( factor, factor, center.x, center.y );
    return *this;
}

Transform&
Transform::scale( const Vector2f& factors, const Vector2f& center )
{
    impl_->transform.scale( factors.x, factors.y, center.x, center.y );
    return *this;
}

Transform
Transform::combine( const Transform& other ) const
{
    Transform result;
    result.impl_->transform = impl_->transform * other.impl_->transform;

    return result;
}

} // namespace gfx_core
