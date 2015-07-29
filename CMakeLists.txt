cmake_minimum_required(VERSION 3.2)
project(Final_Works)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDEBUG")

set (EXAMPLE_PATH src/examples)

set (UTILS src/lib/utils.c src/lib/utils.h)
set (GRAPHICS_LIB src/lib/graphics_lib.c src/lib/graphics_lib.h)
set (MATH_PLOT src/lib/math_plot.c src/lib/math_plot.h)

set(SOURCE_FILES
    src/lib/graphics_lib.c)

#include_directories(src/lib)

add_executable(Final_Works ${SOURCE_FILES})

add_executable(Util_Test src/test/util_test.c ${UTILS})

add_executable(Mine_Sweeper ${EXAMPLE_PATH}/mine_sweeper/mine_sweeper.c ${GRAPHICS_LIB})

add_executable(Chess_Board ${EXAMPLE_PATH}/chessboard/chess_traceback.c ${GRAPHICS_LIB} ${UTILS})