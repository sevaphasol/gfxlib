#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/transformable.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/scrollbar.hpp"
#include "gfx/ui/container_widget.hpp"
#include <memory>

namespace gfx {
namespace ui {

class ScrollableButtonsWidget : public ContainerWidget {
  public:
    explicit ScrollableButtonsWidget( const core::Vector2f& pos  = { 0.0f, 0.0f },
                                      const core::Vector2f& size = { 0.0f, 0.0f } )
        : ContainerWidget( pos, size ), scroll_bar_( 0, 0 )
    {
        setDraggable( true );

        // setPosition( Config::ControlPanel::Size );
        // setSize( Config::ControlPanel::Size );

        border_.setSize( size );
        border_.setFillColor( core::Color::Transparent );
        border_.setOutlineColor( core::Color::Red );
        border_.setOutlineThickness( 2.f );

        scroll_bar_.parent_ = this;
    };

    explicit ScrollableButtonsWidget( float x, float y, float w, float h )
        : ScrollableButtonsWidget( core::Vector2f( x, y ), core::Vector2f( w, h ) )
    {
    }

    virtual ~ScrollableButtonsWidget() = default;

    bool
    propagateEventToChildren( const Event& event ) override
    {
        if ( event.apply( &scroll_bar_ ) )
        {
            return true;
        }

        if ( !buttons_.empty() )
        {
            if ( event.apply( buttons_[current_button_].get() ) )
            {
                return true;
            }
        }

        return false;
    }

    bool
    onIdle( const Event& event ) override
    {
        if ( scroll_bar_.isScrolled() )
        {
            float scroll_factor = scroll_bar_.getScrollFactor();

            current_button_ = ( buttons_.size() - 1 ) * scroll_factor;
        }

        return propagateEventToChildren( event );
    }

    void
    addButton( std::unique_ptr<Button> button )
    {
        button->parent_ = this;
        buttons_.push_back( std::move( button ) );
    }

  private:
    virtual void
    draw( core::Window& window, core::Transform transform ) const override final
    {
        core::Transform widget_transform = transform.combine( getTransform() );

        window.draw( scroll_bar_, widget_transform );
        if ( !buttons_.empty() )
        {
            window.draw( *buttons_[current_button_], widget_transform );
        }

        std::cerr << border_.getSize().x << " " << border_.getSize().y << std::endl;
        std::cerr << border_.getPosition().x << " " << border_.getPosition().y << std::endl;

        window.draw( border_, widget_transform );
    }

  private:
    ScrollBar scroll_bar_;

    gfx::core::RectangleShape border_;

    size_t current_button_ = 0;

    std::vector<std::unique_ptr<Button>> buttons_;
};

} // namespace ui
} // namespace gfx
