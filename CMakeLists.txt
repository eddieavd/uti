#
#       uti
#       CMakeLists.txt
#

cmake_minimum_required( VERSION 3.23 )

project( uti
         VERSION                                   0.0.1
         DESCRIPTION "universal template implementations"
         LANGUAGES                                   CXX
)

add_subdirectory( source/uti )
add_subdirectory(   test/uti )
