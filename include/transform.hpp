#pragma once

#include "vector2.hpp"

#include <SFML/Graphics/Transform.hpp>
#include <memory>

namespace gfx_core {

class Transform {
  public:
    Transform();
    ~Transform();

    Transform( const Transform& other );

    const Transform&
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

inline const Transform Transform::Identity{};

} // namespace gfx_core
