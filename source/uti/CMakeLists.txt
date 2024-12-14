#
#       uti
#       source/uti/CMakeLists.txt
#

add_library( uti )
add_library( uti::uti ALIAS uti )

set_property( TARGET uti PROPERTY SOVERSION "${PROJECT_VERSION}" )

set( UTI_COMPILE_OPTIONS -std=c++26 -Wall -Wextra -pedantic -Werror -ftemplate-backtrace-limit=0 -fconstexpr-backtrace-limit=0 -fno-exceptions -fno-rtti )
target_compile_options( uti PUBLIC "${UTI_COMPILE_OPTIONS}" )

if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set_target_properties( uti PROPERTIES ARCHIVE_OUTPUT_NAME "uti.$<LOWER_CASE:$<CONFIG>>" )
        set_target_properties( uti PROPERTIES LIBRARY_OUTPUT_NAME "uti.$<LOWER_CASE:$<CONFIG>>" )

        set( UTI_DEBUG_OPTIONS   -O0 -DUTI_DEBUG   )
        set( UTI_RELEASE_OPTIONS -O3 -DUTI_RELEASE )

        target_compile_options( uti PUBLIC "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPTIONS}>" )
        target_compile_options( uti PUBLIC "$<$<CONFIG:RELEASE>:${UTI_RELEASE_OPTIONS}>" )
endif()

target_sources( uti PRIVATE uti.cxx )

target_sources( uti PUBLIC
                FILE_SET HEADERS
                BASE_DIRS .
                FILES uti.hxx
)

include( GNUInstallDirs )

install( TARGETS uti
        EXPORT uti
        ARCHIVE
                COMPONENT libuti-dev
        FILE_SET HEADERS
                COMPONENT libuti-dev
        LIBRARY
                COMPONENT libuti
                NAMELINK_COMPONENT libuti-dev
)
install( EXPORT uti
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/uti"
        COMPONENT libuti-dev
        NAMESPACE uti::
)

install( FILES uti.pc
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
        COMPONENT libuti-dev
)
