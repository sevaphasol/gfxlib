#pragma once

#include "gfx/core/vector2.hpp"

namespace gfx {
namespace core {

class Window;

class Mouse {
  public:
    enum Button {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2,

        ButtonCount
    };

    static bool
    isButtonPressed( Button button );

    static Vector2i
    getPosition();

    static Vector2i
    getPosition( const Window& relative_to );

    static void
    setPosition( const Vector2i& position );

    static void
    setPosition( const Vector2i& position, const Window& relative_to );
};

} // namespace core
} // namespace gfx
