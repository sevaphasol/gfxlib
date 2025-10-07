#include "gfx/ui/widget.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/mouse.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"

namespace gfx {
namespace ui {

Widget::Widget( float x, float y, float w, float h ) : size_( w, h ) { setPosition( x, y ); }

Widget::Widget( const core::Vector2f& pos, const core::Vector2f& size ) : size_( size )
{
    setRelPos( pos );
}

bool
Widget::isHoveredSelf() const
{
    return is_hovered_self_;
}

bool
Widget::isHoveredChildren() const
{
    return is_hovered_children_;
}

bool
Widget::isDraggable() const
{
    return is_draggable_;
}

void
Widget::setDraggable( bool state )
{
    is_draggable_ = state;
}

void
Widget::bringToFront( Widget* child )
{
    for ( auto it = children_.begin(); it != children_.end(); ++it )
    {
        if ( it->get() == child )
        {
            auto tmp = std::move( *it );
            children_.erase( it );
            children_.push_back( std::move( tmp ) );
            break;
        }
    }
}

bool
Widget::onIdle( const core::Event::IdleEvent& event )
{
    if ( onIdleChildren( event ) )
    {
        return true;
    }

    return onIdleSelf( event );
}

bool
Widget::onIdleSelf( const core::Event::IdleEvent& event )
{
    return false;
}

bool
Widget::onIdleChildren( const core::Event::IdleEvent& event )
{
    for ( auto it = children_.rbegin(); it != children_.rend(); ++it )
    {
        if ( ( *it )->onIdle( event ) )
        {
            return true;
        }
    }

    return false;
}

bool
Widget::onMousePress( const core::Event::MouseButtonEvent& event )
{
    if ( !is_hovered_self_ && !is_hovered_children_ )
    {
        return false;
    }

    if ( onMousePressChildren( event ) )
    {
        return true;
    }

    return onMousePressSelf( event );
}

bool
Widget::onMousePressSelf( const core::Event::MouseButtonEvent& event )
{
    if ( is_draggable_ && event.button == core::Mouse::Left && is_hovered_self_ )
    {
        if ( parent_ != nullptr )
        {
            parent_->bringToFront( this );
        }

        is_dragging_ = true;

        core::Vector2f mouse_pos( event.x, event.y );
        drag_offset_ = mouse_pos - getAbsPos();

        return true;
    }

    return false;
}

bool
Widget::onMousePressChildren( const core::Event::MouseButtonEvent& event )
{
    for ( auto it = children_.rbegin(); it != children_.rend(); ++it )
    {
        if ( ( *it )->onMousePress( event ) )
        {
            return true;
        }
    }

    return false;
}

bool
Widget::onMouseRelease( const core::Event::MouseButtonEvent& event )
{
    if ( !is_hovered_self_ && !is_hovered_children_ )
    {
        return false;
    }

    if ( onMouseReleaseChildren( event ) )
    {
        return true;
    }

    return onMouseReleaseSelf( event );
}

bool
Widget::onMouseReleaseSelf( const core::Event::MouseButtonEvent& event )
{
    if ( is_dragging_ && event.button == core::Mouse::Left )
    {
        is_dragging_ = false;
        return true;
    }

    return false;
}

bool
Widget::onMouseReleaseChildren( const core::Event::MouseButtonEvent& event )
{
    for ( auto it = children_.rbegin(); it != children_.rend(); ++it )
    {
        if ( ( *it )->onMouseRelease( event ) )
        {
            return true;
        }
    }

    return false;
}

bool
Widget::onMouseMove( const core::Event::MouseMoveEvent& event )
{
    if ( onMouseMoveChildren( event ) )
    {
        return true;
    }

    return onMouseMoveSelf( event );
}

bool
Widget::onMouseMoveSelf( const core::Event::MouseMoveEvent& event )
{
    core::Vector2f mouse_pos( event.x, event.y );
    is_hovered_self_ = pointInside( mouse_pos );

    if ( is_dragging_ )
    {
        setRelPos( mouse_pos - drag_offset_ - getParentAbsPos() );
        return true;
    }

    return is_hovered_self_;
}

bool
Widget::onMouseMoveChildren( const core::Event::MouseMoveEvent& event )
{
    for ( auto it = children_.rbegin(); it != children_.rend(); ++it )
    {
        if ( ( *it )->onMouseMove( event ) )
        {
            is_hovered_children_ = true;
            return true;
        }
    }

    return false;
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
Widget::getParentAbsPos() const
{
    return ( parent_ != nullptr ) ? parent_->getAbsPos() : core::Vector2f( 0, 0 );
}

core::Vector2f
Widget::getAbsPos() const
{
    core::Vector2f rel_pos        = getRelPos();
    core::Vector2f parent_abs_pos = getParentAbsPos();

    return parent_abs_pos + rel_pos;
}

bool
Widget::pointInside( const core::Vector2f& point ) const
{
    core::Vector2f abs_pos = getAbsPos();
    core::Vector2f sz      = getSize();

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
