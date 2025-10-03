#include "gfx_core/font.hpp"
#include <SFML/Graphics/Font.hpp>
#include <memory>

namespace gfx_core {

class Font::Impl {
  public:
    sf::Font font;

    Impl() = default;
};

Font::~Font() = default;

Font::Font() : impl_( std::make_unique<Impl>() ) {}

Font::Font( const std::string& font_filename ) : Font() { loadFromFile( font_filename ); }

Font::Font( const Font& other ) : impl_( std::make_unique<Impl>( *other.impl_ ) ) {}

Font&
Font::operator=( const Font& other )
{
    if ( this != &other )
    {
        impl_ = std::make_unique<Impl>( *other.impl_ );
    }

    return *this;
}

bool
Font::loadFromFile( const std::string& filename )
{
    return impl_->font.loadFromFile( filename );
}

void*
Font::getImpl()
{
    return &impl_->font;
}

const void*
Font::getImpl() const
{
    return &impl_->font;
}

} // namespace gfx_core
