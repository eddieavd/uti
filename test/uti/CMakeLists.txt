#
#       uti
#       test/uti/CMakeLists.txt
#

include( FetchContent )

FetchContent_Declare(
        snitch
        GIT_REPOSITORY https://github.com/snitch-org/snitch.git
        GIT_TAG        v1.3.1
)
FetchContent_GetProperties( snitch )
if( NOT snitch_POPULATED )
        set( FETCHCONTENT_QUIET NO )
        FetchContent_MakeAvailable( snitch )
endif()

add_subdirectory( core )
#add_subdirectory(  sys )
