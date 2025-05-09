#
#       uti
#       bench/uti/CMakeLists.txt
#

include( FetchContent )

set( BENCHMARK_ENABLE_TESTING OFF )

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG        v1.9.1
)
FetchContent_MakeAvailable( benchmark )

add_executable(
        uti.bench
        uti.bench.cxx
)

target_compile_options( uti.bench PRIVATE -std=c++23               )
target_compile_options( uti.bench PRIVATE "${UTI_OPT_LVL}"         )
target_compile_options( uti.bench PRIVATE "${UTI_COMPILE_OPTIONS}" )

target_link_libraries( uti.bench PRIVATE  uti_core::uti_core       )
target_link_libraries( uti.bench PRIVATE benchmark::benchmark      )
target_link_libraries( uti.bench PRIVATE benchmark::benchmark_main )
