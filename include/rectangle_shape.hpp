#pragma once

#include "color.hpp"
#include "drawable.hpp"
#include "transform.hpp"
#include "transformable.hpp"
#include "vector2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

namespace gfx_core {

class RectangleShape : public Drawable, public Transformable {
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

    Vector2f
    getPosition() const;

    virtual void
    draw( Window& window, Transform transform ) const override;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
