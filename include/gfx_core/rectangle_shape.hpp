#pragma once

#include "color.hpp"
#include "drawable.hpp"
#include "transform.hpp"
#include "transformable.hpp"
#include "vector2.hpp"

#include <memory>

namespace gfx_core {

class RectangleShape : public Drawable, public Transformable {
  public:
    RectangleShape( const Vector2f& size = Vector2f( 0, 0 ) );
    ~RectangleShape();
    RectangleShape( const RectangleShape& other );

    void
    setSize( const Vector2f& size );

    Vector2f
    getSize() const;

    void
    setFillColor( const gfx_core::Color& color );

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

} // namespace gfx_core
