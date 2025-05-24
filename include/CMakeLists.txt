#
#       uti
#       include/CMakeLists.txt
#

add_library( uti_core INTERFACE )
add_library( uti_core::uti_core ALIAS uti_core )

if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set( UTI_DEBUG_OPTIONS   -DUTI_DEBUG   )
        set( UTI_RELEASE_OPTIONS -DUTI_RELEASE )

        target_compile_options( uti_core INTERFACE "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPTIONS}>" )
        target_compile_options( uti_core INTERFACE "$<$<CONFIG:RELEASE>:${UTI_RELEASE_OPTIONS}>" )
endif()

if( UTI_HAS_STL )
        target_compile_options( uti_core INTERFACE "-DUTI_HAS_STL" )
endif()

target_sources( uti_core PUBLIC
                FILE_SET HEADERS
                BASE_DIRS .
                FILES uti.core.hxx
)
