#pragma once

#include "gfx/core/transform.hpp"

namespace gfx {
namespace core {

class Window;

class Drawable {
  public:
    virtual ~Drawable() = default;

    virtual void
    draw( Window& target, Transform transform ) const = 0;
};

} // namespace core
} // namespace gfx
