#include "gfx/ui/renderer.hpp"

namespace gfx {
namespace ui {

Renderer::Renderer( gfx::core::Window& window ) : window_( window ) {}

void
Renderer::render( const Widget& root )
{
    renderWidget( root, gfx::core::Transform::Identity );
}

void
Renderer::renderWidget( const Widget& widget, const gfx::core::Transform& parent_transform ) const
{
    gfx::core::Transform widget_transform = parent_transform.combine( widget.getTransform() );
    widget.drawSelf( window_, widget_transform );
    widget.drawChildren( window_, widget_transform );
}

void
Renderer::handleEvent( const gfx::core::Event& event, Widget& root )
{
    bool is_mouse_event = ( event.type == gfx::core::Event::MouseMoved ||
                            event.type == gfx::core::Event::MouseButtonPressed ||
                            event.type == gfx::core::Event::MouseButtonReleased );

    Widget* target_widget = nullptr;
    if ( is_mouse_event )
    {
        gfx::core::Vector2f mouse_pos;
        if ( event.type == gfx::core::Event::MouseMoved )
        {
            mouse_pos = gfx::core::Vector2f( static_cast<float>( event.mouse_move.x ),
                                             static_cast<float>( event.mouse_move.y ) );
            updateHoverState( mouse_pos, root );
        } else
        {
            mouse_pos = gfx::core::Vector2f( static_cast<float>( event.mouse_button.x ),
                                             static_cast<float>( event.mouse_button.y ) );
        }
        target_widget = findWidgetAt( root, mouse_pos );
    }

    if ( target_widget != nullptr )
    {
        propagateEvent( target_widget, event, root );
    } else if ( event.type == gfx::core::Event::Idle )
    {
        root.handleEvent( event, EventPhase::Target );
    }
}

void
Renderer::updateHoverState( const gfx::core::Vector2f& mouse_pos, Widget& root )
{
    Widget* current_hovered = findWidgetAt( root, mouse_pos );

    if ( ( last_hovered_widget_ != nullptr ) && last_hovered_widget_ != current_hovered )
    {
        last_hovered_widget_->setHoveredState( false );
    }

    if ( ( current_hovered != nullptr ) && current_hovered != last_hovered_widget_ )
    {
        current_hovered->setHoveredState( true );
    }

    last_hovered_widget_ = current_hovered;
}

Widget*
Renderer::findWidgetAt( Widget& root, const gfx::core::Vector2f& point )
{
    const auto& children = root.getChildren();
    for ( const auto& child : children )
    {
        Widget* found = findWidgetAt( *child, point );
        if ( found != nullptr )
        {
            return found;
        }
    }

    if ( root.pointInside( point ) )
    {
        return &root;
    }

    return nullptr;
}

void
Renderer::propagateEvent( Widget* target, const gfx::core::Event& event, Widget& root )
{
    std::vector<Widget*> path_to_target;
    Widget*              current = target;
    while ( current != nullptr )
    {
        path_to_target.push_back( current );
        current = current->getParent();
    }

    for ( auto it = path_to_target.end(); it != path_to_target.begin(); --it )
    {
        if ( *it != target )
        {
            ( *it )->handleEvent( event, EventPhase::Capture );
        }

        if ( ( *it )->eventPropagationIsStopped() )
        {
            break;
        }
    }

    if ( !target->eventPropagationIsStopped() )
    {
        target->handleEvent( event, EventPhase::Target );
    }

    if ( !target->eventPropagationIsStopped() )
    {
        for ( auto it = path_to_target.begin(); it != path_to_target.end(); ++it )
        {
            if ( ( *it ) != target )
            {
                ( *it )->handleEvent( event, EventPhase::Bubble );
                if ( ( *it )->eventPropagationIsStopped() )
                {
                    break;
                }
            }
        }
    }
}

} // namespace ui
} // namespace gfx
