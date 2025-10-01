#pragma once

namespace gfx_core {

class Color {
  public:
    unsigned char r, g, b, a;

    constexpr Color() : r( 0 ), g( 0 ), b( 0 ), a( 255 ) {}

    constexpr Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 )
        : r( r ), g( g ), b( b ), a( a )
    {
    }

    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
};

inline constexpr Color Color::White{ 255, 255, 255 };
inline constexpr Color Color::Black{ 0, 0, 0 };
inline constexpr Color Color::Red{ 255, 0, 0 };
inline constexpr Color Color::Green{ 0, 255, 0 };
inline constexpr Color Color::Blue{ 0, 0, 255 };

} // namespace gfx_core
