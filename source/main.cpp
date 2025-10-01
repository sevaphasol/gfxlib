#include "color.hpp"
#include "drawable.hpp"
#include "event.hpp"
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
    draw( gfx_core::Window& window ) const override
    {
        for ( const auto& circle : circles_ )
        {
            window.draw( *circle );
        }
    }

  private:
    std::vector<std::unique_ptr<gfx_core::CircleShape>> circles_;
};

int
main()
{
    gfx_core::Window window( 800, 600, "My Wrapper" );

    Circles circles;

    circles.AddCircle( 100, 100 );
    circles.AddCircle( 100, 200 );
    circles.AddCircle( 100, 300 );

    while ( window.isOpen() )
    {
        gfx_core::Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == gfx_core::Event::Closed )
            {
                window.close();
            }
        }

        window.clear( gfx_core::Color::Blue );
        window.draw( circles );
        window.display();
    }

    return 0;
}
