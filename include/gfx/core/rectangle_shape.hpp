#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/drawable.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/transformable.hpp"
#include "gfx/core/vector2.hpp"

#include <memory>

namespace gfx {
namespace core {

class RectangleShape : public Drawable, public Transformable {
  public:
    RectangleShape( const Vector2f& size = Vector2f( 0, 0 ) );
    ~RectangleShape();
    RectangleShape( const RectangleShape& other );

    void
    setSize( float w, float h );
    void
    setSize( const Vector2f& size );

    Vector2f
    getSize() const;

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
