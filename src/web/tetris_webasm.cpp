// ~/git/emsdk/upstream/emscripten/em++ src/tetris_webasm.cpp src/table.cpp src/tetromino.cpp -std=c++14 -s ASYNCIFY=1 -s WASM=1 -s FETCH=1 -s USE_SDL=2 -s USE_SDL_TTF=2 -O2 --preload-file ocraext.ttf -o index.js && sudo cp index.* score.php /var/www/html/tetris/

#include "table.hpp"
#include "ui_sdl.hpp"

#include <emscripten.h>
#include <emscripten/fetch.h>
#include <cstdlib>
#include <sys/time.h>
#include <string.h>

#include <memory>
#include <string>

struct timeval tv;
unsigned long long prev_time = 0;
unsigned long long current_time = 0;

Table table;

emscripten_fetch_attr_t fetch_attr;
static char request_data[100];

UiPtr gui = std::make_unique<UiSdl>();

void mainloop() {
    gui->clear_background();
    gettimeofday(&tv, NULL);
    gui->draw(table);
    if (gui->game_state == GameState::GAME) {
        gettimeofday(&tv, NULL);
        current_time = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
        const float elapsed_sec = static_cast<float>(current_time - prev_time) / 1000.0f;
        prev_time = current_time;
        const bool end = table.update(elapsed_sec);
        if (end) {
            gui->game_state = GameState::WAIT_FOR_RESTART;
            const std::string requestData = "lines=" + std::to_string(table.get_cleared_lines()) + "&score=" + std::to_string(table.get_score());
            printf("%s\n", requestData.c_str());
            strncpy(request_data, requestData.c_str(), 99);
            fetch_attr.requestData = request_data;
            fetch_attr.requestDataSize = strlen(fetch_attr.requestData);
            emscripten_fetch(&fetch_attr, "http://ongroa.com/tetris/score.php");
            gui->game_state = GameState::WAIT_FOR_RESTART;
        }
    }
    gui->update(table);
}

void post_succeeded(emscripten_fetch_t *fetch) {
    printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    emscripten_fetch_close(fetch);
}

void post_failed(emscripten_fetch_t *fetch) {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    emscripten_fetch_close(fetch);
}

int main() {
    const int simulate_infinite_loop = 1;
    const int fps = -1;
    emscripten_fetch_attr_init(&fetch_attr);
    strcpy(fetch_attr.requestMethod, "POST");
    fetch_attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    fetch_attr.onsuccess = post_succeeded;
    fetch_attr.onerror = post_failed;
    const char *headers[] = {"Content-Type", "application/x-www-form-urlencoded", 0};
    fetch_attr.requestHeaders = headers;
    emscripten_set_main_loop(mainloop, fps, simulate_infinite_loop);

    return EXIT_SUCCESS;
}
