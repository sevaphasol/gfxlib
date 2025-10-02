#pragma once

#include "vector2.hpp"

#include <SFML/Graphics/Transform.hpp>
#include <memory>

namespace gfx_core {

class Transform {
  public:
    Transform();
    ~Transform();

    // clang-format off
	Transform(float a00, float a01, float a02,
	          float a10, float a11, float a12,
	          float a20, float a21, float a22);
    // clang-format on

    Transform( const Transform& other );

    Transform&
    operator=( const Transform& other );

    Transform&
    translate( float x, float y );
    Transform&
    translate( const Vector2f& v );

    Transform&
    rotate( float angle_degrees );
    Transform&
    rotate( float angle_degrees, float center_x, float center_y );
    Transform&
    rotate( float angle_degrees, const Vector2f& center );

    Transform&
    scale( float factor );
    Transform&
    scale( const Vector2f& factors );
    Transform&
    scale( float factor, const Vector2f& center );
    Transform&
    scale( const Vector2f& factors, const Vector2f& center );

    Transform
    combine( const Transform& other ) const;

    static const Transform Identity;

    void*
    getImpl();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
