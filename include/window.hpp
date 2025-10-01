#pragma once

#include "color.hpp"
#include "event.hpp"
#include "mouse.hpp"
#include "vector2.hpp"

#include <memory>

namespace gfx_core {

namespace priv {

class WindowImpl;

}

class Window {
    friend Mouse;

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

  private:
    const void*
    getWindowImpl() const;

  private:
    class WindowImpl;
    std::unique_ptr<WindowImpl> impl_;
};

} // namespace gfx_core
