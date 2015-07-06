cmake_minimum_required(VERSION 3.2)
project(Final_Works)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDEBUG")

set(SOURCE_FILES
    graphics_lib.c)

#include_directories(src/lib)

add_executable(Final_Works ${SOURCE_FILES})