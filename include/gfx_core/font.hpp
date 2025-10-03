#pragma once

#include <memory>
#include <string>

namespace gfx_core {

class Font {
  public:
    Font();
    Font( const std::string& font_filename );
    Font( const Font& other );

    ~Font();

    bool
    loadFromFile( const std::string& filename );

    Font&
    operator=( const Font& other );

    void*
    getImpl();

    const void*
    getImpl() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace gfx_core
