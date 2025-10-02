#pragma once

#include "color.hpp"
#include "vector2.hpp"

namespace gfx_core {

class Vertex {
  public:
    Vertex( const Vector2f& the_position );

    Vertex( const Vector2f& the_position, const Color& the_color );

    Vertex( const Vector2f& the_position, const Vector2f& the_tex_coords );

    Vertex( const Vector2f& the_position, const Color& the_color, const Vector2f& the_tex_coords );

    Vector2f position;
    Color    color;
    Vector2f tex_coords;
};

} // namespace gfx_core
