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

set( UTI_TEST_FILES
        type.test.cxx
        meta.test.cxx
        algo.test.cxx
        iterator.test.cxx
        allocator.test.cxx
        string.test.cxx
        string_view.test.cxx
        string_switch.test.cxx
        tuple.test.cxx
        vector.test.cxx
        prefix_array.test.cxx
        segment_tree.test.cxx
        variant_vector.test.cxx
)

add_executable( uti.test ${UTI_TEST_FILES} )
target_link_libraries( uti.test PRIVATE uti::uti snitch::snitch )

add_test(
        NAME uti.test
        COMMAND uti.test --verbosity high
)
