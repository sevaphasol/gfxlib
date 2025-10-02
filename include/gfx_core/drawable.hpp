#pragma once

#include "transform.hpp"

namespace gfx_core {

class Window;

class Drawable {
  public:
    virtual ~Drawable() = default;

    virtual void
    draw( Window& target, Transform transform ) const = 0;
};

} // namespace gfx_core
