#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/drawable.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rect.hpp"
#include "gfx/core/transformable.hpp"
#include <string>

namespace gfx {
namespace core {

class Text : public Drawable, public Transformable {
  public:
    enum Style {
        Regular       = 0,
        Bold          = 1 << 0,
        Italic        = 1 << 1,
        Underlined    = 1 << 2,
        StrikeThrough = 1 << 3
    };

    ~Text();

    Text();

    Text( const std::string& string, const Font& font, unsigned int character_size );

    void
    setString( const std::string& string );

    void
    setFont( const Font& font );

    void
    setCharacterSize( unsigned int size );

    void
    setStyle( Style style );

    void
    setFillColor( const Color& color );

    void
    setOutlineColor( const Color& color );

    void
    setOutlineThickness( float thickness );

    const std::string&
    getString() const;

    const Font*
    getFont() const;

    unsigned int
    getCharacterSize() const;

    Style
    getStyle() const;

    const Color&
    getFillColor() const;

    const Color&
    getOutlineColor() const;

    float
    getOutlineThickness() const;

    FloatRect
    getLocalBounds() const;

    FloatRect
    getGlobalBounds() const;

    void
    moveInCenterOfRect( const core::Vector2f& rect_size,
                        const core::Vector2f& rect_pos = { 0.0f, 0.0f } );

  private:
    virtual void
    draw( Window& window, Transform transform ) const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace core
} // namespace gfx
