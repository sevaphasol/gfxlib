#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/drawable.hpp"

#include <memory>

namespace gfx {
namespace core {

class Window {
  public:
    Window( unsigned int width, unsigned int height, const char* title );
    ~Window();

    void
    close();

    bool
    isOpen() const;

    Vector2u
    getSize() const;

    void
    clear( const Color& color = Color::Black );

    void
    display();

    bool
    pollEvent( Event& event );

    void
    setFramerateLimit( unsigned int limit );

    void
    draw( const Drawable& drawable, Transform transform = Transform::Identity );

    void
    draw( const Vertex*    vertices,
          std::size_t      vertex_count,
          PrimitiveType    type,
          const Transform& transform = Transform::Identity );

    void*
    getImpl();

    const void*
    getImpl() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace core
} // namespace gfx
