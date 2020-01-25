add_executable(tetris
    tetris.cpp
)

target_link_libraries(tetris
    libtetris
    gui_txt
    ncurses
)

add_executable(tetris-gui
    tetris-gui.cpp
)

target_link_libraries(tetris-gui
    libtetris
    gui_sdl
    SDL2
    SDL2_ttf
)
