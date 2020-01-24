// ~/git/emsdk/upstream/emscripten/em++ src/tetris_webasm.cpp src/table.cpp src/tetromino.cpp -std=c++14 -s ASYNCIFY=1 -s WASM=1 -s FETCH=1 -s USE_SDL=2 -s USE_SDL_TTF=2 -O2 --preload-file ocraext.ttf -o index.js && sudo cp index.* score.php /var/www/html/tetris/

#include "table.hpp"
#include "ui.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <cstdlib>
#include <sys/time.h>
#include <string.h>

#include <memory>
#include <string>

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

struct timeval tv;
unsigned long long prev_time = 0;
unsigned long long current_time = 0;

Table table;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface_message;
SDL_Texture *texture;
SDL_Event event;
SDL_Rect rect;
TTF_Font *font;

emscripten_fetch_attr_t fetch_attr;
static char request_data[100];

// static constexpr int JOYSTICK_DEAD_ZONE = 8000;
SDL_Joystick* gGameController = NULL;

class UiSdl : public Ui {
public:
    UiSdl() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(1);
        }
        if (SDL_NumJoysticks() > 0) {
            gGameController = SDL_JoystickOpen(0);
            puts("detected");
        }
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
        TTF_Init();
        font = TTF_OpenFont("ocraext.ttf", HEIGHT / 30);
        if (font == NULL) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
    }

    ~UiSdl() {
        SDL_JoystickClose(gGameController);
        gGameController = NULL;
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

        static constexpr int TEXT_HEIGHT = HEIGHT / 30;
        static constexpr int TEXT_WIDTH = WIDTH / 4;
        static constexpr int TEXT_X = WIDTH / 3;
        static const SDL_Color color = {255, 255, 255, 0};
        const std::string level_str = "Level: " + std::to_string(table.get_level());
        draw_text(TEXT_X, 0, TEXT_WIDTH, TEXT_HEIGHT, level_str, color);
        const std::string lines_str = "Lines: " + std::to_string(table.get_cleared_lines());
        draw_text(TEXT_X, TEXT_HEIGHT, TEXT_WIDTH, TEXT_HEIGHT, lines_str, color);
        const std::string score_str = "Score: " + std::to_string(table.get_score());
        draw_text(TEXT_X, TEXT_HEIGHT * 2, TEXT_WIDTH, TEXT_HEIGHT, score_str, color);
        const std::string next_str = "Next: ";
        draw_text(TEXT_X, TEXT_HEIGHT * 3, TEXT_WIDTH, TEXT_HEIGHT, next_str, color);
        SDL_RenderPresent(renderer);
    }

    void update(Table& table) override {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (!end && !pause && table.is_empty_left_to_tetromino()) {
                        table.tetromino->move_left();
                    }
                    break;
                case SDLK_RIGHT:
                    if (!end && !pause && table.is_empty_right_to_tetromino()) {
                        table.tetromino->move_right();
                    }
                    break;
                case SDLK_SPACE:
                    while (!end && !pause && table.is_empty_below_tetromino()) {
                        table.tetromino->move_down();
                    }
                    break;
                case SDLK_UP:
                    if (!end && !pause) {
                        table.rotate_tetromino();
                    }
                    break;
                case SDLK_DOWN:
                    if (!end && !pause && table.is_empty_below_tetromino()) {
                        table.tetromino->move_down();
                    }
                    break;
                case SDLK_p:
                    pause = !pause;
                    break;
                case SDLK_r:
                    if (wait_for_restart) {
                        table.init();
                        pause = false;
                        end = false;
                        wait_for_restart = false;
                    }
                    break;
                case SDLK_q:
                    quit = true;
                    break;
                }
                /*
            case SDL_JOYAXISMOTION:
                puts("joystick");
                if (event.jaxis.which == 0 && event.jaxis.axis == 0 && event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                    if (!end && !pause && table.is_empty_left_to_tetromino()) {
                        table.tetromino->move_left();
                    }
                }
                break;
                */
            }
        }
    }

private:
    void draw_rect(const int x, const int y, const char c) const {
        static constexpr int RECT_SIZE = WIDTH / 40;
        static constexpr int BORDER_SIZE = 1;
        rect.x = x * RECT_SIZE + BORDER_SIZE;
        rect.y = y * RECT_SIZE + BORDER_SIZE;
        rect.h = RECT_SIZE - 2 * BORDER_SIZE;
        rect.w = RECT_SIZE - 2 * BORDER_SIZE;
        switch (c) {
            case '#':
                SDL_SetRenderDrawColor(renderer, 90, 90, 90, 0);
                break;
            case 'X':
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
                break;
            case 'O':
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
                break;
            case 'T':
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
                break;
            case 'J':
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                break;
            case 'L':
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                break;
            case 'S':
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
                break;
            case 'Z':
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                break;
            case Tetromino::EMPTY:
                SDL_SetRenderDrawColor(renderer, 51, 51, 51, 0);
                break;
        }
        SDL_RenderFillRect(renderer, &rect);
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

    void draw_text(const int x, const int y, const int w, const int h,
                   const std::string& message, const SDL_Color& color) const {
        surface_message = TTF_RenderText_Solid(font, message.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface_message);
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface_message);
    }

};

UiPtr gui = std::make_unique<UiSdl>();

void mainloop() {
    SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
    SDL_RenderClear(renderer);
    gettimeofday(&tv, NULL);
    gui->draw(table);
    if (!gui->pause) {
        gettimeofday(&tv, NULL);
        current_time = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
        const float elapsed_time = static_cast<float>(current_time - prev_time) / 1000.0f;
        prev_time = current_time;
        if (!gui->end) {
            gui->end = table.update(elapsed_time);
            if (gui->end) {
                const std::string requestData = "lines=" + std::to_string(table.get_cleared_lines()) + "&score=" + std::to_string(table.get_score());
                printf("%s\n", requestData.c_str());
                strncpy(request_data, requestData.c_str(), 99);
                fetch_attr.requestData = request_data;
                fetch_attr.requestDataSize = strlen(fetch_attr.requestData);
                emscripten_fetch(&fetch_attr, "http://ongroa.com/tetris/score.php");
                gui->wait_for_restart = true;
            }
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
