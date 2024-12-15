#
#       uti
#       bench/uti/CMakeLists.txt
#

add_executable(
        uti.bench
        uti.bench.cxx
)
find_package( benchmark REQUIRED )

target_link_libraries( uti.bench PRIVATE       uti::uti            )
target_link_libraries( uti.bench PUBLIC  benchmark::benchmark      )
target_link_libraries( uti.bench PUBLIC  benchmark::benchmark_main )
