include_directories(../lib)

add_executable(tetris
    tetris.cpp
    ui_text.cpp
)

target_link_libraries(tetris
    libtetris
    ncurses
)
