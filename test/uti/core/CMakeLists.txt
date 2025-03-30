#
#       uti
#       test/uti/core/CMakeLists.txt
#

set( UTI_CORE_TEST_FILES
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
        variant.test.cxx
)

add_executable( uti.core.test ${UTI_CORE_TEST_FILES} )

target_compile_options( uti.core.test PRIVATE -std=c++26               )
target_compile_options( uti.core.test PRIVATE "${UTI_OPT_LVL}"         )
target_compile_options( uti.core.test PRIVATE "${UTI_COMPILE_OPTIONS}" )

target_link_libraries( uti.core.test PRIVATE uti_core::uti_core snitch::snitch )

add_test(
        NAME uti.core.test
        COMMAND uti.core.test --verbosity high
)
