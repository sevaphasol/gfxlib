#pragma once

#include "gfx/core/vertex.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/rect.hpp"
#include "gfx/core/drawable.hpp"

#include <memory>

namespace gfx {
namespace core {

class VertexArray : public Drawable {
  public:
    VertexArray();

    explicit VertexArray( PrimitiveType type, std::size_t vertex_count = 0 );

    ~VertexArray();

    VertexArray( const VertexArray& other );

    VertexArray&
    operator=( const VertexArray& other );

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
    draw( Window& target, Transform transform ) const override;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace core
} // namespace gfx
