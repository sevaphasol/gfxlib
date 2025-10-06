#pragma once

#include "gfx/core/vector2.hpp"

#include <algorithm>

namespace gfx {
namespace core {

template<typename T>
class Rect {
  public:
    Rect() : x( 0 ), y( 0 ), w( 0 ), h( 0 ) {}

    Rect( T x, T y, T w, T h ) : x( x ), y( y ), w( w ), h( h ) {}

    Rect( const Vector2<T>& pos, const Vector2<T>& size )
        : x( pos.x ), y( pos.y ), w( size.x ), h( size.y )
    {
    }

    template<typename U>
    explicit Rect( const Rect<U>& rectangle )
        : x( static_cast<T>( rectangle.x ) ), y( static_cast<T>( rectangle.y ) ),
          w( static_cast<T>( rectangle.w ) ), h( static_cast<T>( rectangle.h ) )
    {
    }

    bool
    contains( T x, T y ) const
    {
        T min_x = std::min( x, static_cast<T>( x + w ) );
        T max_x = std::max( x, static_cast<T>( x + w ) );
        T min_y = std::min( y, static_cast<T>( y + h ) );
        T max_y = std::max( y, static_cast<T>( y + h ) );

        return ( x >= min_x ) && ( x < max_x ) && ( y >= min_y ) && ( y < max_y );
    }

    bool
    contains( const Vector2<T>& point ) const
    {
        return contains( point.x, point.y );
    }

    bool
    intersects( const Rect<T>& rectangle ) const
    {
        Rect<T> intersection;
        return intersects( rectangle, intersection );
    }

    bool
    intersects( const Rect<T>& rectangle, Rect<T>& intersection ) const
    {
        T r1_min_x = std::min( x, static_cast<T>( x + w ) );
        T r1_max_x = std::max( x, static_cast<T>( x + w ) );
        T r1_min_y = std::min( y, static_cast<T>( y + h ) );
        T r1_max_y = std::max( y, static_cast<T>( y + h ) );

        T r2_min_x = std::min( rectangle.x, static_cast<T>( rectangle.x + rectangle.w ) );
        T r2_max_x = std::max( rectangle.x, static_cast<T>( rectangle.x + rectangle.w ) );
        T r2_min_y = std::min( rectangle.y, static_cast<T>( rectangle.y + rectangle.h ) );
        T r2_max_y = std::max( rectangle.y, static_cast<T>( rectangle.y + rectangle.h ) );

        T inter_left   = std::max( r1_min_x, r2_min_x );
        T inter_top    = std::max( r1_min_y, r2_min_y );
        T inter_right  = std::min( r1_max_x, r2_max_x );
        T inter_bottom = std::min( r1_max_y, r2_max_y );

        if ( ( inter_left < inter_right ) && ( inter_top < inter_bottom ) )
        {
            intersection = Rect<T>( inter_left,
                                    inter_top,
                                    inter_right - inter_left,
                                    inter_bottom - inter_top );
            return true;
        }

        intersection = Rect<T>( 0, 0, 0, 0 );
        return false;
    }

    Vector2<T>
    getPosition() const
    {
        return Vector2<T>( x, y );
    }

    Vector2<T>
    getSize() const
    {
        return Vector2<T>( w, h );
    }

    T x;
    T y;
    T w;
    T h;
};

template<typename T>
bool
operator==( const Rect<T>& left, const Rect<T>& right )
{
    {
        return ( left.x == right.x ) && ( left.w == right.w ) && ( left.y == right.y ) &&
               ( left.h == right.h );
    }
}

template<typename T>
bool
operator!=( const Rect<T>& left, const Rect<T>& right )
{
    return !( left == right );
}

typedef Rect<int>   IntRect;
typedef Rect<float> FloatRect;

} // namespace core
} // namespace gfx
