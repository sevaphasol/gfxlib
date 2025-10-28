#pragma once
#include "gfx/core/color.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"
#include "gfx/ui/widget_container.hpp"
#include <memory>

namespace gfx {
namespace ui {

class WindowManager {
  public:
    explicit WindowManager( float w, float h, const char* title );
    ~WindowManager() = default;

    void
    run();

    void
    setFramerateLimit( float fps_limit );

    void
    setDeltaTime( float delta_time );

    void
    setBackgroundColor( const gfx::core::Color& color );

    void
    addWidget( std::unique_ptr<gfx::ui::Widget> widget );

  private:
    void
    handleEvents();
    void
    draw();

  private:
    core::Window          window_;
    WidgetVectorContainer desktop_;
    gfx::core::Color      background_color_;
    float                 delta_time_ = 0.0f;
};

} // namespace ui
} // namespace gfx
