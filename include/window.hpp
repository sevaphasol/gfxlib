#pragma once

#include "circle_shape.hpp"
#include "color.hpp"
#include "event.hpp"
#include "mouse.hpp"
#include "rectangle_shape.hpp"
#include "transform.hpp"
#include "vector2.hpp"
#include "drawable.hpp"
#include "vertex_array.hpp"

#include <memory>

namespace gfx_core {

class Window {
    friend Mouse;
    friend CircleShape;
    friend RectangleShape;
    friend VertexArray;

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
    draw( const Drawable& drawable, Transform transform = Transform::Default );

  protected:
    void*
    getImpl() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
