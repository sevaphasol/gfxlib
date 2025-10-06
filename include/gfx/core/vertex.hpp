#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector2.hpp"

namespace gfx {
namespace core {

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

} // namespace core
} // namespace gfx
