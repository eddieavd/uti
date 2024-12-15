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

target_link_libraries( uti.bench PRIVATE       uti::uti            )
target_link_libraries( uti.bench PUBLIC  benchmark::benchmark      )
target_link_libraries( uti.bench PUBLIC  benchmark::benchmark_main )
