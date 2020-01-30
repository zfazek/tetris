add_library(gui_sdl
    ui.cpp
    ui_sdl.cpp
)

add_library(gui_txt
    ui.cpp
    ui_text.cpp
)

target_link_libraries(gui_sdl
    tetris-lib)

target_link_libraries(gui_txt
    tetris-lib)
