#pragma once

#include "color.hpp"
#include "vector2.hpp"

namespace gfx_core {

class Vertex {
  public:
    Vertex();

    Vertex( const Vector2f& position );

    Vertex( const Vector2f& position, const Color& color );

    Vertex( const Vector2f& position, const Vector2f& tex_coords );

    Vertex( const Vector2f& position, const Color& color, const Vector2f& tex_coords );

    Vector2f position;
    Color    color;
    Vector2f tex_coords;
};

} // namespace gfx_core
