#pragma once

#include "gfx/core/drawable.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/transformable.hpp"
#include "gfx/core/vector2.hpp"

#include <vector>
#include <memory>

namespace gfx {
namespace ui {

enum EventPhase { Capture, Target, Bubble };

class Widget : public core::Drawable, public core::Transformable {
  public:
    explicit Widget( float x, float y, float w, float h );
    explicit Widget( const core::Vector2f& pos  = { 0.0f, 0.0f },
                     const core::Vector2f& size = { 0.0f, 0.0f } );
    virtual ~Widget() = default;

    virtual void
    handleEvent( const core::Event& event );

    virtual void
    onIdle( const core::Event& event );

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

    bool
    pointInside( const core::Vector2f& point ) const;

    void
    addChild( std::unique_ptr<Widget> child );

    const std::vector<std::unique_ptr<Widget>>&
    getChildren() const;

    Widget*
    getParent();

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
};

} // namespace ui
} // namespace gfx
