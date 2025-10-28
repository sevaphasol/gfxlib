#include "gfx/ui/widget.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/mouse.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/container_widget.hpp"

namespace gfx {
namespace ui {

Widget::Widget( float x, float y, float w, float h ) : size_( w, h )
{
    setPosition( x, y );
    setSize( size_ );
}

Widget::Widget( const core::Vector2f& pos, const core::Vector2f& size ) : size_( size )
{
    setRelPos( pos );
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

bool
Widget::onIdle( const Event& event )
{
    return false;
}

bool
Widget::onKeyPress( const Event& event )
{
    return false;
}

bool
Widget::onKeyRelease( const Event& event )
{
    return false;
}

bool
Widget::onMousePress( const Event& event )
{
    if ( event.info.mouse_button.button == core::Mouse::Left && is_hovered_ )
    {
        is_pressed_ = true;

        ContainerWidget* parent_container = dynamic_cast<ContainerWidget*>( parent_ );

        if ( parent_container != nullptr )
        {
            parent_container->bringToFront( this );
        }

        if ( is_draggable_ )
        {
            is_dragging_ = true;

            core::Vector2f mouse_pos( event.info.mouse_button.x, event.info.mouse_button.y );
            drag_offset_ = mouse_pos - getAbsPos();
        }

        return true;
    }

    return false;
}

bool
Widget::onMouseRelease( const Event& event )
{
    is_pressed_ = false;

    if ( is_dragging_ && event.info.mouse_button.button == core::Mouse::Left )
    {
        is_dragging_ = false;
        return true;
    }

    return false;
}

bool
Widget::onMouseMove( const Event& event )
{

    core::Vector2f mouse_pos( event.info.mouse_move.x, event.info.mouse_move.y );
    is_hovered_ = pointInside( mouse_pos );

    if ( !is_hovered_ )
    {
        is_pressed_ = false;
    }

    if ( is_dragging_ )
    {
        setRelPos( mouse_pos - drag_offset_ - getParentAbsPos() );
        return true;
    }

    return is_hovered_;
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

Widget*
Widget::getParent()
{
    return parent_;
}

void
Widget::draw( core::Window& window, core::Transform transform ) const
{
    core::Transform widget_transform = transform.combine( getTransform() );
}

} // namespace ui
} // namespace gfx
