#pragma once

#include "vector2.hpp"

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
    scale( float factor );
    Transform&
    scale( float x, float y );

    Transform
    combine( const Transform& other ) const;

    static const Transform Default;

    void*
    getImpl();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

inline const Transform Transform::Default{};

} // namespace gfx_core
