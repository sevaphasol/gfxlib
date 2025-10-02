#include "primitive_type.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>

namespace gfx_core {
namespace detail {

sf::PrimitiveType
toSFML( PrimitiveType type )
{
    switch ( type )
    {
        case PrimitiveType::Points:
            return sf::Points;
        case PrimitiveType::Lines:
            return sf::Lines;
        case PrimitiveType::LineStrip:
            return sf::LineStrip;
        case PrimitiveType::Triangles:
            return sf::Triangles;
        case PrimitiveType::TriangleStrip:
            return sf::TriangleStrip;
        case PrimitiveType::TriangleFan:
            return sf::TriangleFan;
        default:
            return sf::Triangles;
    }
}

PrimitiveType
fromSFML( sf::PrimitiveType type )
{
    switch ( type )
    {
        case sf::Points:
            return PrimitiveType::Points;
        case sf::Lines:
            return PrimitiveType::Lines;
        case sf::LineStrip:
            return PrimitiveType::LineStrip;
        case sf::Triangles:
            return PrimitiveType::Triangles;
        case sf::TriangleStrip:
            return PrimitiveType::TriangleStrip;
        case sf::TriangleFan:
            return PrimitiveType::TriangleFan;
        default:
            return PrimitiveType::Triangles;
    }
}

} // namespace detail
} // namespace gfx_core
