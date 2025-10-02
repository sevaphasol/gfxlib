#pragma once

#include "color.hpp"
#include "event.hpp"
#include "transform.hpp"
#include "drawable.hpp"

#include <memory>

namespace gfx_core {

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

    void*
    getImpl() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
