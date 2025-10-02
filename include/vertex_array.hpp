#pragma once

#include "vertex.hpp"
#include "primitive_type.hpp"
#include "rect.hpp"
#include "drawable.hpp"

#include <memory>

namespace gfx_core {

namespace impl {

class VertexArray;

}

class VertexArray : public Drawable {
  public:
    VertexArray();

    explicit VertexArray( PrimitiveType type, std::size_t vertex_count = 0 );

    ~VertexArray();

    std::size_t
    getVertexCount() const;

    Vertex&
    operator[]( std::size_t index );

    const Vertex&
    operator[]( std::size_t index ) const;

    void
    clear();

    void
    resize( std::size_t vertex_count );

    void
    append( const Vertex& vertex );

    void
    setPrimitiveType( PrimitiveType type );

    PrimitiveType
    getPrimitiveType() const;

    FloatRect
    getBounds() const;

  private:
    virtual void
    draw( Window& target ) const override;

  private:
    std::unique_ptr<impl::VertexArray> impl_;
};

} // namespace gfx_core
