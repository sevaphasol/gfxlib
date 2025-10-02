#pragma once

#include "transform.hpp"

namespace gfx_core {

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
    Vector2f          origin_;
    Vector2f          position_;
    float             rotation_;
    Vector2f          scale_;
    mutable Transform transform_;
    mutable bool      transform_need_update_;
};

} // namespace gfx_core
