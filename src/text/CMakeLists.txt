set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror -Wextra -g -O2")

include_directories(../lib)

add_executable(tetris
    tetris.cpp
    ui_text.cpp
)

target_link_libraries(tetris
    libtetris
    ncurses
)
