#include "gfx_core/vertex_array.hpp"
#include "gfx_core/window.hpp"
#include "gfx_core/primitive_type.hpp"
#include "gfx_core/vertex.hpp"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

static_assert( sizeof( gfx_core::Vertex ) == sizeof( sf::Vertex ) );
static_assert( offsetof( gfx_core::Vertex, position ) == offsetof( sf::Vertex, position ) );
static_assert( offsetof( gfx_core::Vertex, color ) == offsetof( sf::Vertex, color ) );
static_assert( offsetof( gfx_core::Vertex, tex_coords ) == offsetof( sf::Vertex, texCoords ) );

namespace gfx_core {

namespace detail {

extern sf::PrimitiveType
toSFML( PrimitiveType type );

extern PrimitiveType
fromSFML( sf::PrimitiveType type );

} // namespace detail

class VertexArray::Impl {
  public:
    sf::VertexArray vertices;

    Impl() = default;
    Impl( PrimitiveType type, std::size_t vertex_count )
        : vertices( detail::toSFML( type ), vertex_count )
    {
    }
};

VertexArray::VertexArray() : impl_( std::make_unique<Impl>() ) {}

VertexArray::~VertexArray() = default;

VertexArray::VertexArray( const VertexArray& other )
    : impl_( std::make_unique<Impl>( *other.impl_ ) )
{
}

VertexArray&
VertexArray::operator=( const VertexArray& other )
{
    if ( this != &other )
    {
        impl_ = std::make_unique<Impl>( *other.impl_ );
    }

    return *this;
}

VertexArray::VertexArray( PrimitiveType type, std::size_t vertex_count )
    : impl_( std::make_unique<Impl>( type, vertex_count ) )
{
}

std::size_t
VertexArray::getVertexCount() const
{
    return impl_->vertices.getVertexCount();
}

Vertex&
VertexArray::operator[]( std::size_t index )
{
    return *reinterpret_cast<Vertex*>( &impl_->vertices[index] );
}

const Vertex&
VertexArray::operator[]( std::size_t index ) const
{
    return *reinterpret_cast<const Vertex*>( &impl_->vertices[index] );
}

void
VertexArray::clear()
{
    impl_->vertices.clear();
}

void
VertexArray::resize( std::size_t vertex_count )
{
    impl_->vertices.resize( vertex_count );
}

void
VertexArray::append( const Vertex& vertex )
{
    impl_->vertices.append( *reinterpret_cast<const sf::Vertex*>( &vertex ) );
}

void
VertexArray::setPrimitiveType( PrimitiveType type )
{
    impl_->vertices.setPrimitiveType( detail::toSFML( type ) );
}

PrimitiveType
VertexArray::getPrimitiveType() const
{
    return detail::fromSFML( impl_->vertices.getPrimitiveType() );
}

FloatRect
VertexArray::getBounds() const
{
    sf::FloatRect sf_bounds = impl_->vertices.getBounds();
    return FloatRect{ sf_bounds.left, sf_bounds.top, sf_bounds.width, sf_bounds.height };
}

void
VertexArray::draw( Window& target, Transform transform ) const
{
    auto* sf_window    = static_cast<sf::RenderWindow*>( target.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( transform.getImpl() );

    sf_window->draw( impl_->vertices, *sf_transform );
}

} // namespace gfx_core
