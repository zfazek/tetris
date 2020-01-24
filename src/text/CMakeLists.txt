include_directories(../gui)
include_directories(../lib)

add_executable(tetris
    tetris.cpp
)

target_link_libraries(tetris
    libtetris
    gui_txt
    ncurses
)
