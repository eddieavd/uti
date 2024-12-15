#
#       uti
#       CMakeLists.txt
#

cmake_minimum_required( VERSION 3.23 )

project( uti
         VERSION      0.0.1
         DESCRIPTION "uti - universal template implementations"
         LANGUAGES    CXX
)

add_subdirectory( source )

if( UTI_TEST )
        add_subdirectory( test/uti )
endif()

if( UTI_BENCH )
        add_subdirectory( bench/uti )
endif()
