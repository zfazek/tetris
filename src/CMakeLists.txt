project(tetris)

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror -Wextra -g -O2")

add_executable(tetris
    tetris.cpp
    tetromino.cpp
    table.cpp
    ui_text.cpp
)

target_link_libraries(tetris
    ncurses
)
