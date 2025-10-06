cmake_minimum_required( VERSION 3.16 )

project( gfx LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

find_package( PkgConfig REQUIRED )
pkg_check_modules( SFML REQUIRED IMPORTED_TARGET sfml-graphics sfml-window sfml-system )

file( GLOB_RECURSE GFX_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gfx/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gfx/ui/*.cpp
)

add_library( gfx STATIC ${GFX_SOURCES} )

target_include_directories( gfx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( gfx PRIVATE PkgConfig::SFML )

if( CMAKE_PROJECT_NAME STREQUAL "gfx" )
    file( GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp
    )
    if( EXAMPLE_SOURCES )
        add_executable( gfx_example ${EXAMPLE_SOURCES} )
        target_link_libraries( gfx_example PRIVATE gfx )
        set( CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" )
        install( TARGETS gfx_example DESTINATION bin )
    endif()
endif()
