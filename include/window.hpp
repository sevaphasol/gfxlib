#pragma once

#include "circle_shape.hpp"
#include "color.hpp"
#include "event.hpp"
#include "mouse.hpp"
#include "rectangle_shape.hpp"
#include "vector2.hpp"
#include "drawable.hpp"

#include <memory>

namespace gfx_core {

namespace impl {

class Window;

}

class Window {
    friend Mouse;
    friend CircleShape;
    friend RectangleShape;

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
    draw( const Drawable& drawable );

  protected:
    void*
    getWindowImpl() const;

  private:
    std::unique_ptr<impl::Window> impl_;
};

} // namespace gfx_core
