#pragma once

namespace gfx_core {

class Window;

class Drawable {
  public:
    virtual ~Drawable() = default;

    virtual void
    draw( Window& target ) const = 0;
};

} // namespace gfx_core
