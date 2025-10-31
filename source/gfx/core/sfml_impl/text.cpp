#include "gfx/core/color.hpp"
#include "gfx/core/drawable.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rect.hpp"
#include "gfx/core/window.hpp"
#include "gfx/core/text.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>

#include <memory>
#include <string>

namespace gfx {
namespace core {

namespace detail {

sf::Text::Style
toSFML( Text::Style style )
{
    switch ( style )
    {
        case Text::Style::Regular:
            return sf::Text::Style::Regular;
        case Text::Style::Bold:
            return sf::Text::Style::Bold;
        case Text::Style::Italic:
            return sf::Text::Style::Italic;
        case Text::Style::Underlined:
            return sf::Text::Style::Underlined;
        case Text::Style::StrikeThrough:
            return sf::Text::Style::StrikeThrough;
        default:
            return sf::Text::Style::Regular;
    }
}

Text::Style
fromSFML( sf::Text::Style style )
{
    switch ( style )
    {
        case sf::Text::Style::Regular:
            return Text::Style::Regular;
        case sf::Text::Style::Bold:
            return Text::Style::Bold;
        case sf::Text::Style::Italic:
            return Text::Style::Italic;
        case sf::Text::Style::Underlined:
            return Text::Style::Underlined;
        case sf::Text::Style::StrikeThrough:
            return Text::Style::StrikeThrough;
        default:
            return Text::Style::Regular;
    }
}

} // namespace detail

class Text::Impl {
  public:
    sf::Text text;

    Impl() = default;
};

Text::~Text() = default;

Text::Text() : impl_( std::make_unique<Impl>() ) {}

void
Text::setString( const std::string& string )
{
    impl_->text.setString( string );
}

std::string
Text::getString() const
{
    return impl_->text.getString();
}

void
Text::setFont( const Font& font )
{
    const auto* sf_font = static_cast<const sf::Font*>( font.getImpl() );

    impl_->text.setFont( *sf_font );
}

void
Text::setCharacterSize( unsigned int size )
{
    impl_->text.setCharacterSize( size );
}

void
Text::setStyle( Text::Style style )
{
    impl_->text.setStyle( detail::toSFML( style ) );
}

void
Text::setFillColor( const Color& color )
{
    impl_->text.setFillColor( sf::Color( color.r, color.g, color.b, color.a ) );
}

void
Text::setOutlineColor( const Color& color )
{
    impl_->text.setOutlineColor( sf::Color( color.r, color.g, color.b, color.a ) );
}

void
Text::setOutlineThickness( float thickness )
{
    impl_->text.setOutlineThickness( thickness );
}

FloatRect
Text::getLocalBounds() const
{
    auto sf_rect      = impl_->text.getLocalBounds();
    auto sf_rect_pos  = sf_rect.getPosition();
    auto sf_rect_size = sf_rect.getSize();

    return FloatRect( sf_rect_pos.x, sf_rect_pos.y, sf_rect_size.x, sf_rect_size.y );
}

FloatRect
Text::getGlobalBounds() const
{
    auto sf_rect      = impl_->text.getGlobalBounds();
    auto sf_rect_pos  = sf_rect.getPosition();
    auto sf_rect_size = sf_rect.getSize();

    return FloatRect( sf_rect_pos.x, sf_rect_pos.y, sf_rect_size.x, sf_rect_size.y );
}

void
Text::moveInCenterOfRect( const core::Vector2f& rect_size, const core::Vector2f& rect_pos )
{
    const core::FloatRect text_bounds = getLocalBounds();
    setOrigin( text_bounds.x + text_bounds.w / 2.0f, text_bounds.y + text_bounds.h / 2.0f );
    setPosition( rect_pos.x + rect_size.x / 2.0f, rect_pos.y + rect_size.y / 2.0f );
}

void
Text::draw( Window& window, Transform transform ) const
{
    Transform local_transform = transform.combine( getTransform() );

    auto* sf_window    = static_cast<sf::RenderWindow*>( window.getImpl() );
    auto* sf_transform = static_cast<sf::Transform*>( local_transform.getImpl() );

    sf_window->draw( impl_->text, *sf_transform );
}

} // namespace core
} // namespace gfx
