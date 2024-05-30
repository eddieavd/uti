include( FetchContent )

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/16f637fbf4ffc3f7a01fa4eceb7906634565242f.zip
)
FetchContent_MakeAvailable( googletest )

enable_testing()

add_executable(
        gtest_uti
        gtest_uti.cpp
        gtest_traits.cpp
        gtest_tuple.cpp
        gtest_vector.cpp
        gtest_prefix.cpp
)
target_link_libraries(
        gtest_uti
        gtest_main
)
target_include_directories(
        gtest_uti
        PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include
)

include( GoogleTest )
gtest_discover_tests( gtest_uti )
