#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/drawable.hpp"
#include "gfx/core/transformable.hpp"

#include <memory>

namespace gfx {
namespace core {

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
    setFillColor( const Color& color );

    void
    setOutlineThickness( float thickness );

    void
    setOutlineColor( const Color& color );

    virtual void
    draw( Window& window, Transform transform ) const override;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace core
} // namespace gfx
