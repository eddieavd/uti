#
#       uti
#       bench/uti/CMakeLists.txt
#

include( FetchContent )

set( BENCHMARK_ENABLE_TESTING OFF )

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.9.1
)
FetchContent_MakeAvailable( benchmark )

add_executable(
        uti.bench
        uti.bench.cxx
)

set( UTI_BENCH_COMPILE_OPTIONS -std=c++23
                               -Wall -Wextra -pedantic
                               -ftemplate-backtrace-limit=0
                               -fconstexpr-backtrace-limit=0
                               -fno-exceptions -fno-rtti
)
target_compile_options( uti.bench PRIVATE "${UTI_BENCH_COMPILE_OPTIONS}" )

if( CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES )
        set( UTI_DEBUG_OPTIONS   -O0 )
        set( UTI_RELEASE_OPTIONS -O3 )

        target_compile_options( uti.bench PRIVATE "$<$<CONFIG:DEBUG>:${UTI_DEBUG_OPTIONS}>" )
        target_compile_options( uti.bench PRIVATE "$<$<CONFIG:RELEASE>:${UTI_RELEASE_OPTIONS}>" )
endif()

target_link_libraries( uti.bench PRIVATE       uti::uti            )
target_link_libraries( uti.bench PRIVATE benchmark::benchmark      )
target_link_libraries( uti.bench PRIVATE benchmark::benchmark_main )
