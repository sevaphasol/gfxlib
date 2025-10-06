#include "gfx/ui/widget.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"

#include <cassert>
#include <iostream>

namespace gfx {
namespace ui {

Widget::Widget( float x, float y, float w, float h ) : size_( w, h ) { setPosition( x, y ); }

Widget::Widget( const core::Vector2f& pos, const core::Vector2f& size ) : size_( size )
{
    setRelPos( pos );
}

void
Widget::handleEvent( const core::Event& event )
{
    for ( auto& child : children_ )
    {
        child->handleEvent( event );
    }

    if ( event.type == core::Event::Idle )
    {
        onIdle( event );
    }
}

void
Widget::onIdle( const core::Event& event )
{
}

core::Vector2f
Widget::getSize() const
{
    return size_;
}

void
Widget::setSize( const core::Vector2f& size )
{
    size_ = size;
}

core::Vector2f
Widget::getRelPos() const
{
    return getPosition();
}

void
Widget::setRelPos( const core::Vector2f& pos )
{
    setPosition( pos );
}

core::Vector2f
Widget::getAbsPos() const
{
    core::Vector2f rel_pos = getRelPos();
    core::Vector2f parent_abs_pos =
        ( parent_ != nullptr ) ? parent_->getAbsPos() : core::Vector2f( 0, 0 );

    return parent_abs_pos + rel_pos;
}

bool
Widget::pointInside( const core::Vector2f& point ) const
{
    core::Vector2f abs_pos = getAbsPos();
    core::Vector2f sz      = getSize();

    std::cerr << "abs_pos = " << abs_pos.x << " " << abs_pos.y << std::endl;

    return ( ( point.x >= abs_pos.x && point.x <= abs_pos.x + sz.x ) &&
             ( point.y >= abs_pos.y && point.y <= abs_pos.y + sz.y ) );
}

void
Widget::addChild( std::unique_ptr<Widget> child )
{
    child->parent_ = this;
    children_.push_back( std::move( child ) );
}

const std::vector<std::unique_ptr<Widget>>&
Widget::getChildren() const
{
    return children_;
}

Widget*
Widget::getParent()
{
    return parent_;
}

void
Widget::draw( core::Window& window, core::Transform transform ) const
{
    core::Transform widget_transform = transform.combine( getTransform() );
    drawSelf( window, widget_transform );
    drawChildren( window, widget_transform );
}

void
Widget::drawSelf( core::Window& window, core::Transform transform ) const
{
}

void
Widget::drawChildren( core::Window& window, core::Transform transform ) const
{
    for ( const auto& child : children_ )
    {
        window.draw( *child, transform );
    }
}

} // namespace ui
} // namespace gfx
