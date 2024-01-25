cmake_minimum_required( VERSION 3.21 )

project( uti VERSION 0.0.1 )

option( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_CXX_STANDARD          23   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

add_compile_options( -Wall -Wextra -pedantic -Werror )

if( UTI_RELEASE )
        add_compile_options( -O3 )
        add_compile_definitions( UTI_RELEASE )
elseif( UTI_DEBUG )
        add_compile_options( -O0 )
        add_compile_definitions( UTI_DEBUG )
        add_link_options( -fsanitize=address -fsanitize=undefined )
endif()

if( UTI_HAS_STL )
        add_compile_definitions( UTI_HAS_STL )
endif()

if( UTI_TEST )
        add_subdirectory( test )
endif()

if( UTI_BENCH )
        add_subdirectory( bench )
endif()

add_executable( uti main.cpp )

target_include_directories( uti PUBLIC include )
