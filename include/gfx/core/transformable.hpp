#pragma once

#include "gfx/core/transform.hpp"

namespace gfx {
namespace core {

class Transformable {
  public:
    Transformable();

    void
    setPosition( float x, float y );

    void
    setPosition( const Vector2f& position );

    void
    setRotation( float angle );

    void
    setScale( float factor_x, float factor_y );

    void
    setScale( const Vector2f& factors );

    void
    setOrigin( float x, float y );

    void
    setOrigin( const Vector2f& origin );

    Vector2f
    getPosition() const;

    float
    getRotation() const;

    Vector2f
    getScale() const;

    Vector2f
    getOrigin() const;

    void
    move( float offset_x, float offset_y );

    void
    move( const Vector2f& offset );

    void
    rotate( float angle );

    void
    scale( float factor_x, float factor_y );

    void
    scale( const Vector2f& factor );

    const Transform&
    getTransform() const;

    const Transform&
    getInverseTransform() const;

  private:
    Vector2f          origin_{ 0.0f, 0.0f };
    Vector2f          position_{ 0.0f, 0.0f };
    float             rotation_{ 0.0f };
    Vector2f          scale_{ 1.0f, 1.0f };
    mutable Transform transform_;
    mutable bool      transform_need_update_{ true };
};

} // namespace core
} // namespace gfx
