#pragma once

#include "gfx/core/drawable.hpp"
#include "gfx/ui/event.hpp"
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

    // clang-format off
    virtual bool onIdle   		( const Event& event );
    virtual bool onKeyPress     ( const Event& event );
    virtual bool onKeyRelease   ( const Event& event );
    virtual bool onMousePress   ( const Event& event );
    virtual bool onMouseRelease ( const Event& event );
    virtual bool onMouseMove    ( const Event& event );
    // clang-format on

    bool
    isHovered() const;

    bool
    isDraggable() const;
    void
    setDraggable( bool state );

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

    Widget* parent_ = nullptr;

  protected:
    core::Vector2f size_;

    bool is_pressed_ = false;

    bool           is_draggable_ = false;
    bool           is_dragging_  = false;
    core::Vector2f drag_offset_  = { 0.0f, 0.0f };

    bool is_hovered_ = false;
};

} // namespace ui
} // namespace gfx
