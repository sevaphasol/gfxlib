#include "vertex.hpp"
#include "color.hpp"
#include "vector2.hpp"

namespace gfx_core {

Vertex::Vertex( const Vector2f& the_position )
{
    position   = the_position;
    color      = Color::White;
    tex_coords = Vector2f( 0, 0 );
}

Vertex::Vertex( const Vector2f& the_position, const Color& the_color )
{
    position   = the_position;
    color      = the_color;
    tex_coords = Vector2f( 0, 0 );
}

Vertex::Vertex( const Vector2f& the_position, const Vector2f& the_tex_coords )
{
    position   = the_position;
    color      = Color::White;
    tex_coords = the_tex_coords;
}

Vertex::Vertex( const Vector2f& the_position,
                const Color&    the_color,
                const Vector2f& the_tex_coords )
{
    position   = the_position;
    color      = the_color;
    tex_coords = the_tex_coords;
}

} // namespace gfx_core
