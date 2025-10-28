#pragma once

#include <iostream>
#include "gfx/core/vector2.hpp"
#include "gfx/ui/event.hpp"
#include "gfx/ui/widget.hpp"
#include <memory>

namespace gfx {
namespace ui {

class WidgetContainer : public Widget {
  public:
    explicit WidgetContainer( float x, float y, float w, float h ) : Widget( x, y, w, h ) {}
    explicit WidgetContainer( const core::Vector2f& pos  = { 0.0f, 0.0f },
                              const core::Vector2f& size = { 0.0f, 0.0f } )
        : Widget( pos, size ) {};
    virtual ~WidgetContainer() = default;

    virtual void
    bringToFront( Widget* child ) = 0;

    virtual bool
    propagateEventToChildren( const Event& event ) = 0;

    virtual bool
    onIdle( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onIdle( event );
    }

    virtual bool
    onKeyPress( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onKeyPress( event );
    }

    virtual bool
    onKeyRelease( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onKeyRelease( event );
    }

    virtual bool
    onMousePress( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMousePress( event );
    }

    virtual bool
    onMouseRelease( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMouseRelease( event );
    }

    virtual bool
    onMouseMove( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMouseMove( event );
    }
};

class WidgetVectorContainer : public WidgetContainer {
  public:
    explicit WidgetVectorContainer( float x, float y, float w, float h )
        : WidgetContainer( x, y, w, h )
    {
    }
    explicit WidgetVectorContainer( const core::Vector2f& pos  = { 0.0f, 0.0f },
                                    const core::Vector2f& size = { 0.0f, 0.0f } )
        : WidgetContainer( pos, size ) {};
    virtual ~WidgetVectorContainer() = default;

    virtual bool
    onIdle( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }
    virtual bool
    onKeyPress( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }
    virtual bool
    onKeyRelease( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }
    virtual bool
    onMousePress( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }
    virtual bool
    onMouseRelease( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }
    virtual bool
    onMouseMove( const Event& event ) override
    {
        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        return propagateEventToChildren( event );
    }

    void
    addChild( std::unique_ptr<Widget> child )
    {
        child->parent_ = this;
        children_.emplace_back( std::move( child ) );
    }

    virtual bool
    propagateEventToChildren( const Event& event ) override
    {
        for ( auto& child : children_ )
        {
            if ( event.apply( child.get() ) )
            {
                return true;
            }
        }

        return false;
    }

    void
    bringToFront( Widget* child ) override
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

    void
    drawChildren( core::Window& window, core::Transform transform ) const
    {
        for ( const auto& child : children_ )
        {
            child->draw( window, transform );
        }
    }

    void
    draw( core::Window& window, core::Transform transform ) const override
    {
        core::Transform widget_transform = transform.combine( getTransform() );
        drawChildren( window, widget_transform );
    }

  protected:
    std::vector<std::unique_ptr<Widget>> children_;
};

} // namespace ui
} // namespace gfx
