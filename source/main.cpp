#include "event.hpp"
#include "window.hpp"

int
main()
{
    gfx_core::Window window( 800, 600, "My Wrapper" );

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
        window.display();
    }

    return 0;
}
