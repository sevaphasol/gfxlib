#pragma once

#include <cmath>

namespace gfx {
namespace core {

template<typename T>
class Vector3 {
  public:
    T x{};
    T y{};
    T z{};

    constexpr Vector3() : x( 0 ), y( 0 ), z( 0 ) {}

    constexpr Vector3( T X, T Y, T Z ) : x( X ), y( Y ), z( Z ) {}

    template<typename U>
    constexpr Vector3( const Vector3<U>& vector )
        : x( static_cast<T>( vector.x ) ), y( static_cast<T>( vector.y ) ),
          z( static_cast<T>( vector.z ) )
    {
    }

    constexpr friend Vector3<T>
    operator-( const Vector3<T>& right )
    {
        return Vector3<T>( -right.x, -right.y, -right.z );
    }

    constexpr friend Vector3<T>&
    operator+=( Vector3<T>& left, const Vector3<T>& right )
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;

        return left;
    }

    constexpr friend Vector3<T>&
    operator-=( Vector3<T>& left, const Vector3<T>& right )
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;

        return left;
    }

    constexpr friend Vector3<T>
    operator+( const Vector3<T>& left, const Vector3<T>& right )
    {
        return Vector3<T>( left.x + right.x, left.y + right.y, left.z + right.z );
    }

    constexpr friend Vector3<T>
    operator-( const Vector3<T>& left, const Vector3<T>& right )
    {
        return Vector3<T>( left.x - right.x, left.y - right.y, left.z - right.z );
    }

    constexpr friend Vector3<T>
    operator*( const Vector3<T>& left, T right )
    {
        return Vector3<T>( left.x * right, left.y * right, left.z * right );
    }

    constexpr friend Vector3<T>
    operator*( T left, const Vector3<T>& right )
    {
        return Vector3<T>( right.x * left, right.y * left, right.z * left );
    }

    constexpr friend Vector3<T>&
    operator*=( Vector3<T>& left, T right )
    {
        left.x *= right;
        left.y *= right;
        left.z *= right;

        return left;
    }

    constexpr friend Vector3<T>
    operator/( const Vector3<T>& left, const Vector3<T>& right )
    {
        return Vector3<T>( left.x / right.x, left.y / right.y, left.z / right.z );
    }

    constexpr friend Vector3<T>
    operator/=( Vector3<T>& left, const Vector3<T>& right )
    {
        left.x /= right.x;
        left.y /= right.y;
        left.z /= right.z;

        return left;
    }

    constexpr friend Vector3<T>
    operator/( const Vector3<T>& left, T right )
    {
        return Vector3<T>( left.x / right, left.y / right, left.z / right );
    }

    constexpr friend Vector3<T>&
    operator/=( Vector3<T>& left, T right )
    {
        left.x /= right;
        left.y /= right;
        left.z /= right;

        return left;
    }

    constexpr friend bool
    operator==( const Vector3<T>& left, const Vector3<T>& right )
    {
        return ( left.x == right.x ) && ( left.y == right.y ) && ( left.z == right.z );
    }

    constexpr friend bool
    operator!=( const Vector3<T>& left, const Vector3<T>& right )
    {
        return ( left.x != right.x ) || ( left.y != right.y ) || ( left.z != right.z );
    }

    constexpr bool
    valid() const
    {
        return !( std::isnan( x ) || std::isnan( y ) || std::isnan( z ) );
    }

    constexpr friend T
    scalarMul( const Vector3<T> left, const Vector3<T> right )
    {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    constexpr friend T
    calcCos( const Vector3<T>& left, const Vector3<T>& right )
    {
        return scalarMul( left, right ) / ( left.getLen() * right.getLen() );
    }

    constexpr friend float
    calcSin( const Vector3<T>& left, const Vector3<T>& right )
    {
        return std::sin( std::acos( calcCos( left, right ) ) );
    }

    constexpr friend float
    vectorMulModule( const Vector3<T>& left, const Vector3<T>& right )
    {
        return left.getLen() * right.getLen() * calcSin( left, right );
    }

    constexpr float
    getLenSq() const
    {
        return scalarMul( *this, *this );
    }

    constexpr float
    getLen() const
    {
        return std::sqrt( getLenSq() );
    }

    constexpr Vector3<T>
    normalize()
    {
        float len = getLen();
        x /= len;
        y /= len;
        z /= len;

        return *this;
    }

    constexpr Vector3<T>
    calcReflected( const Vector3<T>& normal ) const
    {
        return *this + normal * 2;
    }

    static const Vector3<T> Nan;
};

template<typename T>
inline const Vector3<T> Vector3<T>::Nan( std::numeric_limits<T>::quiet_NaN(),
                                         std::numeric_limits<T>::quiet_NaN(),
                                         std::numeric_limits<T>::quiet_NaN() );

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;

} // namespace core
} // namespace gfx
