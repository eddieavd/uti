#
#       uti
#       source/CMakeLists.txt
#

add_library( uti INTERFACE )
add_library( uti::uti ALIAS uti )

set_property( TARGET uti PROPERTY SOVERSION "${PROJECT_VERSION}" )

if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set( UTI_DEBUG_OPTIONS   -DUTI_DEBUG   )
        set( UTI_RELEASE_OPTIONS -DUTI_RELEASE )

        target_compile_options( uti INTERFACE "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPTIONS}>" )
        target_compile_options( uti INTERFACE "$<$<CONFIG:RELEASE>:${UTI_RELEASE_OPTIONS}>" )
endif()

if( UTI_HAS_STL )
        target_compile_options( uti INTERFACE "-DUTI_HAS_STL" )
endif()

target_sources( uti PUBLIC
                FILE_SET HEADERS
                BASE_DIRS .
                FILES uti.hxx
)
