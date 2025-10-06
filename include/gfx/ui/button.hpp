#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "gfx/ui/widget.hpp"

namespace gfx {
namespace ui {

class Button : public Widget {
  public:
    explicit Button( const core::Vector2f& pos  = { 0, 0.0f },
                     const core::Vector2f& size = { 0, 0.0f } );

    void
    setLabelText( const std::string& text );

    void
    setLabelFont( const core::Font& font, size_t size );

    void
    setBackgroundColor( const core::Color& color );

    void
    setPressed( bool pressed );
    void
    setHovered( bool hovered );

    virtual void
    setSize( const core::Vector2f& size ) override;

    virtual void
    setRelPos( const core::Vector2f& pos ) override;

    virtual void
    handleEvent( const core::Event& event ) override;

    virtual void
    onIdle( const core::Event& event ) override;
    virtual void
    onMousePress( const core::Event& event );
    virtual void
    onMouseRelease( const core::Event& event );
    virtual void
    onMouseMove( const core::Event& event );

    bool
    isPressed() const;
    bool
    isHovered() const;

  protected:
    virtual void
    updateVisuals();

  private:
    void
    drawSelf( core::Window& window, core::Transform transform ) const override;

    bool pressed_ = false;
    bool hovered_ = false;

    core::RectangleShape background_;
    core::Text           label_;
};

} // namespace ui
} // namespace gfx
