// ~/git/emsdk/upstream/emscripten/em++ src/tetris_webasm.cpp src/table.cpp src/tetromino.cpp -std=c++14 -s ASYNCIFY=1 -s WASM=1 -s USE_SDL=2 -O2 -o index.js && sudo cp index.* /var/www/html/tetris/

#include <SDL2/SDL.h>
#include <emscripten.h>
#include <cstdlib>

#include "table.hpp"
#include "ui.hpp"

#include <chrono>
#include <thread>
#include <memory>

static constexpr int WIDTH = 400;
static constexpr int HEIGHT = 300;

Table table;

SDL_Rect rect;

SDL_Window *window;
SDL_Renderer *renderer;

int get_rand_int(const int max) {
    return rand() % max;
}

class UiSdl : public Ui {
public:
    UiSdl() {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    }

    ~UiSdl() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw(const Table& table) const override {
        for (int j = 0; j < table.WIDTH + 2; ++j) {
            draw_rect(j, 0, '#');
            draw_rect(j, table.HEIGHT + 1, '#');
        }
        for (int i = 0; i < table.HEIGHT; ++i) {
            for (int j = 0; j < table.WIDTH; ++j) {
                const char c = table.buffer[i][j];
                if (c != Tetromino::EMPTY) {
                    draw_rect(j + 1, i + 1, c);
                }
                draw_rect(0, i + 1, '#');
                draw_rect(table.WIDTH + 1, i + 1, '#');
            }
        }
        draw_tetromino(table);
        draw_next_tetromino(table);
    }

    void update(Table& table) override {
    }

private:
    void draw_rect(const int x, const int y, const char c) const {
        static constexpr int RECT_SIZE = 10;
        rect.x = x * RECT_SIZE;
        rect.y = y * RECT_SIZE;
        rect.h = RECT_SIZE;
        rect.w = RECT_SIZE;
        switch (c) {
            case '#':
                SDL_SetRenderDrawColor(renderer, 90, 90, 90, 0);
                break;
            case 'X':
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
                break;
            case Tetromino::EMPTY:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        }
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    void draw_tetromino(const Table& table) const {
        for (int i = 0; i < table.tetromino->SIZE; ++i) {
            for (int j = 0; j < table.tetromino->SIZE; ++j) {
                if (table.tetromino->buffer[i][j] == table.tetromino->get_block()) {
                    draw_rect(table.tetromino->x + j + 1,
                              table.tetromino->y + i + 1,
                              table.tetromino->buffer[i][j]);
                }
            }
        }
    }

    void draw_next_tetromino(const Table& table) const {
        for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
            for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
                draw_rect(table.next_tetromino->x + j + 1,
                          table.next_tetromino->y + i + 1,
                          Tetromino::EMPTY);
            }
        }
        for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
            for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
                if (table.next_tetromino->buffer[i][j] == table.next_tetromino->get_block()) {
                    draw_rect(table.next_tetromino->x + j + 1,
                              table.next_tetromino->y + i + 1,
                              table.next_tetromino->buffer[i][j]);
                }
            }
        }
    }

};

UiPtr gui = std::make_unique<UiSdl>();

void mainloop() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    std::chrono::system_clock::time_point prev_time = std::chrono::system_clock::now();
    gui->draw(table);
    if (!gui->pause) {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        float elapsed_time = std::chrono::duration<float, std::milli>(current_time - prev_time).count() / 1000.0f;
        prev_time = current_time;
        if (!gui->end) {
            gui->end = table.update(elapsed_time);
        }
    }
    gui->update(table);
}

int main() {
    const int simulate_infinite_loop = 1;
    const int fps = -1;
    emscripten_set_main_loop(mainloop, fps, simulate_infinite_loop);

    return EXIT_SUCCESS;
}
