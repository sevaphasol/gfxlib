#pragma once

#include "color.hpp"
#include "drawable.hpp"
#include "vector2.hpp"

#include <memory>

namespace gfx_core {

class RectangleShape : public gfx_core::Drawable {
  public:
    RectangleShape( const Vector2f& size = Vector2f( 0, 0 ) );
    ~RectangleShape();

    void
    setSize( const Vector2f& size );

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
    getRectangleShapeImpl() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
