#include "color.hpp"
#include "drawable.hpp"
#include "event.hpp"
#include "mouse.hpp"
#include "primitive_type.hpp"
#include "rectangle_shape.hpp"
#include "transform.hpp"
#include "vector2.hpp"
#include "vertex_array.hpp"
#include "window.hpp"
#include "circle_shape.hpp"
#include <memory>
#include <vector>

class Circles : public gfx_core::Drawable {
  public:
    void
    AddCircle( float x, float y )
    {
        auto p = std::make_unique<gfx_core::CircleShape>( 10.0f );
        p->setFillColor( gfx_core::Color::Green );
        p->setPosition( x, y );

        circles_.push_back( std::move( p ) );
    }

  private:
    virtual void
    draw( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        for ( const auto& circle : circles_ )
        {
            window.draw( *circle );
        }
    }

  private:
    std::vector<std::unique_ptr<gfx_core::CircleShape>> circles_;
};

class RotatingRects : public gfx_core::Drawable {
  public:
    void
    AddRect( float x, float y )
    {
        auto p = std::make_unique<gfx_core::RectangleShape>( gfx_core::Vector2f( 20.0f, 20.0f ) );
        p->setFillColor( gfx_core::Color::Green );
        p->setPosition( x, y );

        rects_.push_back( std::move( p ) );
    }

  private:
    virtual void
    draw( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        for ( const auto& rect : rects_ )
        {
            gfx_core::Transform ctransform = transform;

            window.draw( *rect, ctransform.rotate( angle, rect->getPosition() ) );
        }
    }

  public:
    float angle;

  private:
    std::vector<std::unique_ptr<gfx_core::RectangleShape>> rects_;
};

int
main()
{
    gfx_core::Window window( 800, 600, "My Wrapper" );

    Circles circles;
    circles.AddCircle( 100, 100 );
    circles.AddCircle( 100, 200 );
    circles.AddCircle( 100, 300 );

    RotatingRects rects;
    rects.AddRect( 200, 100 );
    rects.AddRect( 200, 200 );
    rects.AddRect( 200, 300 );

    gfx_core::VertexArray vertex_array( gfx_core::PrimitiveType::TriangleStrip );

    vertex_array.append( gfx_core::Vertex( { 300, 100 }, gfx_core::Color::Red ) );
    vertex_array.append( gfx_core::Vertex( { 400, 200 }, gfx_core::Color::Red ) );
    vertex_array.append( gfx_core::Vertex( { 500, 100 }, gfx_core::Color::Red ) );

    bool pressed = false;

    while ( window.isOpen() )
    {
        gfx_core::Event event;
        while ( window.pollEvent( event ) )
        {
            switch ( event.type )
            {
                case gfx_core::Event::Closed:
                    window.close();
                    break;
                case gfx_core::Event::MouseButtonPressed:
                    pressed = true;
                    break;
                case gfx_core::Event::MouseButtonReleased:
                    pressed = false;
                    break;
                default:
                    break;
            }
        }

        rects.angle += 0.01f;

        if ( pressed )
        {
            vertex_array[1].position = gfx_core::Mouse::getPosition( window );
        }

        window.clear( gfx_core::Color::Blue );
        window.draw( circles );
        window.draw( rects );
        window.draw( vertex_array );
        window.display();
    }

    return 0;
}
