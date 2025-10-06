#include "gfx/ui/widget.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"

#include <cassert>

namespace gfx {
namespace ui {

Widget::Widget( float x, float y, float w, float h ) : size_( w, h ) { setPosition( x, y ); }

Widget::Widget( const core::Vector2f& pos, const core::Vector2f& size ) : size_( size )
{
    setPosition( pos );
}

void
Widget::handleEvent( const core::Event& event, EventPhase phase )
{
    switch ( phase )
    {
        case Capture:
            handleCapturePhase( event );
            break;
            return;
        case Target:
            handleTargetPhase( event );
            break;
        case Bubble:
            handleBubblePhase( event );
            break;
        default:
            assert( !"unknown EventPhase" );
            break;
    }

    if ( phase != EventPhase::Target && !event_propagation_stopped_ )
    {
        for ( auto& child : children_ )
        {
            if ( !event_propagation_stopped_ )
            {
                child->handleEvent( event, phase );
            }
        }
    }
}

void
Widget::handleCapturePhase( const core::Event& event )
{
}

void
Widget::handleTargetPhase( const core::Event& event )
{
    switch ( event.type )
    {
        case core::Event::MouseButtonPressed:
            onMousePress( event );
            break;
        case core::Event::MouseMoved:
            onMouseMove( event );
            break;
        case core::Event::Idle:
            onIdle( event );
            break;
        default:
            assert( !"Unsupported event type" );
            break;
    }
}

void
Widget::handleBubblePhase( const core::Event& event )
{
}

void
Widget::onMousePress( const core::Event& event )
{
}

void
Widget::onMouseMove( const core::Event& event )
{
}

void
Widget::onIdle( const core::Event& event )
{
    update();
}

bool
Widget::eventPropagationIsStopped() const
{
    return event_propagation_stopped_;
}

void
Widget::stopEventPropagation()
{
    event_propagation_stopped_ = true;
}

void
Widget::update()
{
    for ( auto& child : children_ )
    {
        child->update();
    }
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
Widget::isHovered() const
{
    return is_hovered_;
}

void
Widget::setHoveredState( bool hovered )
{
    is_hovered_ = hovered;
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
