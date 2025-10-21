#pragma once

#include "gfx/core/drawable.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/transformable.hpp"
#include "gfx/core/vector2.hpp"

#include <vector>
#include <memory>

namespace gfx {
namespace ui {

class Widget : public core::Drawable, public core::Transformable {
  public:
    explicit Widget( float x, float y, float w, float h );
    explicit Widget( const core::Vector2f& pos  = { 0.0f, 0.0f },
                     const core::Vector2f& size = { 0.0f, 0.0f } );
    virtual ~Widget() = default;

    bool
    onIdle( const core::Event::IdleEvent& event );
    virtual bool
    onIdleSelf( const core::Event::IdleEvent& event );
    virtual bool
    onIdleChildren( const core::Event::IdleEvent& event );

    bool
    onKeyPress( const core::Event::KeyEvent& event );
    virtual bool
    onKeyPressSelf( const core::Event::KeyEvent& event );
    virtual bool
    onKeyPressChildren( const core::Event::KeyEvent& event );

    bool
    onKeyRelease( const core::Event::KeyEvent& event );
    virtual bool
    onKeyReleaseSelf( const core::Event::KeyEvent& event );
    virtual bool
    onKeyReleaseChildren( const core::Event::KeyEvent& event );

    bool
    onMousePress( const core::Event::MouseButtonEvent& event );
    virtual bool
    onMousePressSelf( const core::Event::MouseButtonEvent& event );
    virtual bool
    onMousePressChildren( const core::Event::MouseButtonEvent& event );

    bool
    onMouseRelease( const core::Event::MouseButtonEvent& event );
    virtual bool
    onMouseReleaseSelf( const core::Event::MouseButtonEvent& event );
    virtual bool
    onMouseReleaseChildren( const core::Event::MouseButtonEvent& event );

    bool
    onMouseMove( const core::Event::MouseMoveEvent& event );
    virtual bool
    onMouseMoveSelf( const core::Event::MouseMoveEvent& event );
    virtual bool
    onMouseMoveChildren( const core::Event::MouseMoveEvent& event );

    void
    bringToFront( Widget* child );

    bool
    isHoveredSelf() const;
    bool
    isHoveredChildren() const;

    bool
    isDraggable() const;
    void
    setDraggable( bool state );

    void
    addChild( std::unique_ptr<Widget> child );
    const std::vector<std::unique_ptr<Widget>>&
    getChildren() const;
    Widget*
    getParent();

    core::Vector2f
    getSize() const;
    virtual void
    setSize( const core::Vector2f& size );
    core::Vector2f
    getRelPos() const;
    virtual void
    setRelPos( const core::Vector2f& pos );
    core::Vector2f
    getAbsPos() const;
    core::Vector2f
    getParentAbsPos() const;
    bool
    pointInside( const core::Vector2f& point ) const;

    void
    draw( core::Window& window, core::Transform transform ) const override;
    virtual void
    drawSelf( core::Window& window, core::Transform transform ) const;
    virtual void
    drawChildren( core::Window& window, core::Transform transform ) const;

  protected:
    core::Vector2f size_;

    std::vector<std::unique_ptr<Widget>> children_;

    Widget* parent_ = nullptr;

    bool is_pressed_ = false;

    bool           is_draggable_ = false;
    bool           is_dragging_  = false;
    core::Vector2f drag_offset_  = { 0.0f, 0.0f };

    bool is_hovered_self_     = false;
    bool is_hovered_children_ = false;
};

} // namespace ui
} // namespace gfx
