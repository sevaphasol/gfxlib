#include "gfx/core/color.hpp"
#include "gfx/core/drawable.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/mouse.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "gfx/core/transform.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/vertex_array.hpp"
#include "gfx/core/window.hpp"
#include "gfx/core/circle_shape.hpp"
#include <memory>
#include <vector>

class Circles : public gfx::core::Drawable {
  public:
    void
    AddCircle( float x, float y )
    {
        auto p = std::make_unique<gfx::core::CircleShape>( 10.0f );
        p->setFillColor( gfx::core::Color::Green );
        p->setPosition( x, y );
        p->setOutlineColor( gfx::core::Color::Red );
        p->setOutlineThickness( 2 );

        circles_.push_back( std::move( p ) );
    }

  private:
    virtual void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
        for ( const auto& circle : circles_ )
        {
            window.draw( *circle );
        }
    }

  private:
    std::vector<std::unique_ptr<gfx::core::CircleShape>> circles_;
};

class RotatingRects : public gfx::core::Drawable {
  public:
    void
    AddRect( float x, float y )
    {
        auto p = std::make_unique<gfx::core::RectangleShape>( gfx::core::Vector2f( 20.0f, 20.0f ) );
        p->setFillColor( gfx::core::Color::Transparent );
        p->setPosition( x, y );
        p->setOrigin( 10, 10 );
        p->setOutlineColor( gfx::core::Color::Black );
        p->setOutlineThickness( 2 );

        rects_.push_back( std::move( p ) );
    }

  private:
    virtual void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
        for ( const auto& rect : rects_ )
        {
            rect->setRotation( angle );
            window.draw( *rect );
        }
    }

  public:
    float angle;

  private:
    std::vector<std::unique_ptr<gfx::core::RectangleShape>> rects_;
};

int
main()
{
    gfx::core::Window window( 800, 600, "My Wrapper" );

    Circles circles;
    circles.AddCircle( 100, 100 );
    circles.AddCircle( 100, 200 );
    circles.AddCircle( 100, 300 );

    RotatingRects rects;
    rects.AddRect( 200, 100 );
    rects.AddRect( 200, 200 );
    rects.AddRect( 200, 300 );

    rects.angle = 0;

    gfx::core::VertexArray vertex_array( gfx::core::PrimitiveType::TriangleStrip );

    vertex_array.append( gfx::core::Vertex( { 300, 100 }, gfx::core::Color::Red ) );
    vertex_array.append( gfx::core::Vertex( { 370, 130 }, gfx::core::Color::Red ) );
    vertex_array.append( gfx::core::Vertex( { 400, 100 }, gfx::core::Color::Red ) );
    vertex_array.append( gfx::core::Vertex( { 400, 200 }, gfx::core::Color::Red ) );

    gfx::core::Font font( "examples/assets/JetBrainsMono-Regular.ttf" );
    gfx::core::Text text( "Test", font, 24 );
    text.setPosition( 500, 500 );

    gfx::core::Vertex vertices[2];

    vertices[0].position = { 500, 100 };
    vertices[0].color    = gfx::core::Color::Red;
    vertices[1].position = { 600, 200 };
    vertices[1].color    = gfx::core::Color::Red;

    bool pressed = false;

    window.setFramerateLimit( 60 );

    while ( window.isOpen() )
    {
        gfx::core::Event event;
        while ( window.pollEvent( event ) )
        {
            switch ( event.type )
            {
                case gfx::core::Event::Closed:
                    window.close();
                    break;
                case gfx::core::Event::MouseButtonPressed:
                    pressed = true;
                    break;
                case gfx::core::Event::MouseButtonReleased:
                    pressed = false;
                    break;
                default:
                    break;
            }
        }

        rects.angle += 1.0f;

        if ( pressed )
        {
            vertex_array[1].position = gfx::core::Mouse::getPosition( window );
        }

        window.clear( gfx::core::Color::Blue );
        window.draw( circles );
        window.draw( rects );
        window.draw( text );
        window.draw( vertex_array );
        window.draw( vertices, 2, gfx::core::PrimitiveType::Lines );
        window.display();
    }

    return 0;
}
