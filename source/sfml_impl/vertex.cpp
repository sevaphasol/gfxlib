#include "gfx_core/vertex.hpp"
#include "gfx_core/color.hpp"
#include "gfx_core/vector2.hpp"

namespace gfx_core {

Vertex::Vertex()
    : position( Vector2f( 0, 0 ) ), color( Color::White ), tex_coords( Vector2f( 0, 0 ) )
{
}

Vertex::Vertex( const Vector2f& position )
    : position( position ), color( Color::White ), tex_coords( Vector2f( 0, 0 ) )
{
}

Vertex::Vertex( const Vector2f& position, const Color& color )
    : position( position ), color( color ), tex_coords( Vector2f( 0, 0 ) )
{
}

Vertex::Vertex( const Vector2f& position, const Vector2f& tex_coords )
    : position( position ), color( Color::White ), tex_coords( tex_coords )
{
}

Vertex::Vertex( const Vector2f& position, const Color& color, const Vector2f& tex_coords )
    : position( position ), color( color ), tex_coords( tex_coords )
{
}

} // namespace gfx_core
