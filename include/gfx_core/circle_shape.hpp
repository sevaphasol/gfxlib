#pragma once

#include "color.hpp"
#include "drawable.hpp"
#include "transformable.hpp"

#include <memory>

namespace gfx_core {

class CircleShape : public Drawable, public Transformable {
  public:
    ~CircleShape();
    explicit CircleShape( float radius = 0.0f );
    CircleShape( const CircleShape& other );

    void
    setRadius( float radius );

    float
    getRadius() const;

    void
    setFillColor( const gfx_core::Color& color );

    virtual void
    draw( Window& window, Transform transform ) const override;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
