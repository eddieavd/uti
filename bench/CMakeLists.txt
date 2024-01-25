add_executable(
        gbench_uti
        gbench_uti.cpp
)

find_package( benchmark REQUIRED )

target_link_libraries( gbench_uti PUBLIC benchmark::benchmark      )
target_link_libraries( gbench_uti PUBLIC benchmark::benchmark_main )

target_include_directories(
        gbench_uti
        PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include
)
