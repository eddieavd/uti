#
#       uti
#       test/uti/CMakeLists.txt
#

include( FetchContent )

set( SNITCH_WITH_EXCEPTIONS 0 )

FetchContent_Declare(
        snitch
        GIT_REPOSITORY https://github.com/snitch-org/snitch.git
        GIT_TAG        v1.3.1
)
FetchContent_MakeAvailable( snitch )

add_subdirectory( core )
add_subdirectory(  sys )
