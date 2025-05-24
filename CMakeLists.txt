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

set( UTI_COMPILE_OPTIONS -Wall -Wextra -pedantic
                         -ftemplate-backtrace-limit=0
                         -fconstexpr-backtrace-limit=0
                         -fno-exceptions -fno-rtti
)
if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set( UTI_DEBUG_OPT_LVL   -O0 )
        set( UTI_RELEASE_OPT_LVL -O3 )

        set( UTI_OPT_LVL "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPT_LVL}>"
                         "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPT_LVL}>"
        )
endif()

add_subdirectory( include )
add_subdirectory(  source )

if( UTI_TEST )
        add_subdirectory( test/uti )
endif()

if( UTI_BENCH )
        add_subdirectory( bench/uti )
endif()
