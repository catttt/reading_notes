cmake_minimum_required( VERSION 2.8 ) 
project( hello ) 

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable( main main.cpp )