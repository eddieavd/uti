#
#       uti
#       test/uti/sys/CMakeLists.txt
#

set( UTI_SYS_TEST_FILES
        sys.test.cxx
)

add_executable( uti.sys.test ${UTI_SYS_TEST_FILES} )

target_compile_options( uti.sys.test PRIVATE -std=c++26               )
target_compile_options( uti.sys.test PRIVATE "${UTI_OPT_LVL}"         )
target_compile_options( uti.sys.test PRIVATE "${UTI_COMPILE_OPTIONS}" )

target_link_libraries( uti.sys.test PRIVATE uti_sys::uti_sys snitch::snitch )

add_test(
        NAME uti.sys.test
        COMMAND uti.sys.test --verbosity high
)
