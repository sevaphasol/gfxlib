#include "transformable.hpp"
#include "transform.hpp"
#include "vector2.hpp"

#include <cmath>

namespace gfx_core {

Transformable::Transformable() = default;

void
Transformable::setPosition( float x, float y )
{
    position_              = Vector2f( x, y );
    transform_need_update_ = true;
}

void
Transformable::setPosition( const Vector2f& position )
{
    position_              = position;
    transform_need_update_ = true;
}

void
Transformable::setRotation( float angle )
{
    rotation_              = angle;
    transform_need_update_ = true;
}

void
Transformable::setScale( float x, float y )
{
    scale_                 = Vector2f( x, y );
    transform_need_update_ = true;
}

void
Transformable::setScale( const Vector2f& factors )
{
    scale_                 = factors;
    transform_need_update_ = true;
}

void
Transformable::setOrigin( float x, float y )
{
    origin_                = Vector2f( x, y );
    transform_need_update_ = true;
}

void
Transformable::setOrigin( const Vector2f& origin )
{
    origin_                = origin;
    transform_need_update_ = true;
}

Vector2f
Transformable::getPosition() const
{
    return position_;
}

float
Transformable::getRotation() const
{
    return rotation_;
}

Vector2f
Transformable::getScale() const
{
    return scale_;
}

Vector2f
Transformable::getOrigin() const
{
    return origin_;
}

void
Transformable::move( float offset_x, float offset_y )
{
    setPosition( position_ + Vector2f( offset_x, offset_y ) );
}

void
Transformable::move( const Vector2f& offset )
{
    setPosition( position_ + offset );
}

void
Transformable::rotate( float angle )
{
    setRotation( rotation_ + angle );
}

void
Transformable::scale( float factor_x, float factor_y )
{
    setScale( { scale_.x * factor_x, scale_.y * factor_y } );
}

void
Transformable::scale( const Vector2f& factor )
{
    setScale( { scale_.x * factor.x, scale_.y * factor.y } );
}

const Transform&
Transformable::getTransform() const
{
    if ( transform_need_update_ )
    {
        const float angle  = ( -rotation_ / 180.0f ) * M_PI;
        const float cosine = std::cos( angle );
        const float sine   = std::sin( angle );
        const float sxc    = scale_.x * cosine;
        const float syc    = scale_.y * cosine;
        const float sxs    = scale_.x * sine;
        const float sys    = scale_.y * sine;
        const float tx     = -origin_.x * sxc - origin_.y * sys + position_.x;
        const float ty     = origin_.x * sxs - origin_.y * syc + position_.y;

        // clang-format off
        transform_ = Transform( sxc, sys, tx,
                                -sxs, syc, ty,
                                0.f, 0.f, 1.f);
        // clang-format on

        transform_need_update_ = false;
    }

    return transform_;
}

} // namespace gfx_core
