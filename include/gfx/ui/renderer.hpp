#pragma once

#include "gfx/core/window.hpp"
#include "gfx/core/event.hpp"
#include "gfx/ui/widget.hpp"

namespace gfx {
namespace ui {

class Renderer {
  public:
    Renderer( gfx::core::Window& window );

    void
    render( const Widget& root );

    void
    handleEvent( const gfx::core::Event& event, Widget& root );

    void
    updateHoverState( const gfx::core::Vector2f& mouse_pos, Widget& root );

  private:
    void
    renderWidget( const Widget& widget, const gfx::core::Transform& parent_transform ) const;

    Widget*
    findWidgetAt( Widget& root, const gfx::core::Vector2f& point );

    static void
    propagateEvent( Widget* target, const gfx::core::Event& event, Widget& root );

  private:
    gfx::core::Window& window_;
    Widget*            last_hovered_widget_ = nullptr;
};

} // namespace ui
} // namespace gfx
