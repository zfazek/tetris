# emconfigure cmake ..
# cp ../ocraext.ttf ../index.html src/web/
# emmake make index
# sudo cp src/web/index.* ../score.php /var/www/html/tetris

set(CMAKE_EXE_LINKER_FLAGS "-s ASYNCIFY=1 -s WASM=1 -s FETCH=1 -s USE_SDL=2 -s USE_SDL_TTF=2 --preload-file ocraext.ttf")

add_executable(index
    tetris_webasm.cpp
)

target_link_libraries(index
    gui_sdl
)
