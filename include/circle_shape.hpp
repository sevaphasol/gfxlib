#pragma once

#include "color.hpp"
#include "drawable.hpp"
#include "vector2.hpp"

#include <memory>

namespace gfx_core {

namespace impl {

class CircleShape;

}

class CircleShape : public gfx_core::Drawable {
  public:
    CircleShape( float radius = 0.0f );
    ~CircleShape();

    void
    setRadius( float radius );

    void
    setFillColor( const gfx_core::Color& color );

    void
    setPosition( float x, float y );

    void
    setPosition( const gfx_core::Vector2f& pos );

    virtual void
    draw( Window& window ) const override;

  private:
    void*
    getCircleShapeImpl() const;

  private:
    std::unique_ptr<impl::CircleShape> impl_;
};

} // namespace gfx_core
