cmake_minimum_required( VERSION 3.21 )

project( uti VERSION 0.0.1 )

option( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_CXX_STANDARD          23   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

add_compile_options( -Wall -Wextra -pedantic -Werror -O0 )
add_link_options( -fsanitize=address -fsanitize=undefined )

if( UTI_TEST )
        add_subdirectory( test )
endif()

if( UTI_BENCH )
        add_subdirectory( bench )
endif()

add_executable( uti           main.cpp )
add_executable( uti_test test/main.cpp )

target_include_directories( uti      PUBLIC include )
target_include_directories( uti_test PUBLIC include )
