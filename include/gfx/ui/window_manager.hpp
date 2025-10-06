#pragma once
#include "gfx/core/window.hpp"
#include "gfx/ui/renderer.hpp"
#include "gfx/ui/widget.hpp"

namespace gfx {
namespace ui {

class WindowManager {
  public:
    explicit WindowManager( float w, float h, const char* title );
    virtual ~WindowManager() = default;

    void
    run();

    void
    setFramerateLimit( float fps_limit );

    void
    setDeltaTime( float delta_time );

  private:
    void
    handleEvents();
    void
    draw();

  protected:
    Widget desktop_;

  private:
    core::Window window_;
    Renderer     renderer_;
    float        delta_time_ = 0.0f;
};

} // namespace ui
} // namespace gfx
