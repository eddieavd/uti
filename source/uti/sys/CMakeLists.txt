#
#       uti
#       source/uti/sys/CMakeLists.txt
#

add_library( uti_sys )
add_library( uti_sys::uti_sys ALIAS uti_sys )

set_property( TARGET uti_sys PROPERTY SOVERSION "${PROJECT_VERSION}" )

if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set( UTI_DEBUG_OPTIONS -DUTI_DEBUG )
        set( UTI_RELEASE_OPTIONS -DUTI_RELESE )

        set_target_properties( uti_sys PROPERTIES ARCHIVE_OUTPUT_NAME "uti_sys.$<LOWER_CASE:$<CONFIG>>" )
        set_target_properties( uti_sys PROPERTIES LIBRARY_OUTPUT_NAME "uti_sys.$<LOWER_CASE:$<CONFIG>>" )

        target_compile_options( uti_sys PRIVATE "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPTIONS}>" )
        target_compile_options( uti_sys PRIVATE "$<$<CONFIG:RELEASE>:${UTI_RELEASE_OPTIONS}>" )
endif()

if( UTI_HAS_STL )
        target_compile_options( uti_sys PRIVATE "-DUTI_HAS_STL" )
endif()

target_sources( uti_sys PRIVATE
        test.cxx
)
target_sources( uti_sys PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
#       FILES uti.sys.hxx
)
target_link_libraries( uti_sys PRIVATE
        uti_core::uti_core
)
