cmake_minimum_required(VERSION 3.2)
project(C_Cli_Graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -DDEBUG")

set (EXAMPLE_PATH src/examples)

set (UTILS src/lib/utils.c src/lib/utils.h)
set (GRAPHICS_LIB src/lib/graphics_lib.c src/lib/graphics_lib.h)
set (MATH_PLOT src/lib/math_plot.c src/lib/math_plot.h)
set (LINKED_LIST src/lib/linked_list.c src/lib/linked_list.h)
set (QUEUE src/lib/queue.c src/lib/queue.c ${LINKED_LIST})

set(SOURCE_FILES
    src/lib/graphics_lib.c)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include_directories(src/lib)

#add_executable(Final_Works ${SOURCE_FILES})

add_executable(Util_Test src/test/util_test.c ${UTILS})
add_executable(Linked_List_Test src/test/linked_list_test.c ${LINKED_LIST})

add_executable(Mine_Sweeper ${EXAMPLE_PATH}/mine_sweeper/mine_sweeper.c ${GRAPHICS_LIB})

add_executable(Plot_A_Circle ${EXAMPLE_PATH}/plot_a_circle/plot_a_circle.c ${GRAPHICS_LIB} ${MATH_PLOT})

add_executable(Chess_Board ${EXAMPLE_PATH}/chessboard/chess_traceback.c ${GRAPHICS_LIB} ${UTILS} ${QUEUE})