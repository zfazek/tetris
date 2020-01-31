#include "ui_sdl.hpp"

UiSdl::UiSdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);
    SDL_SetWindowTitle(window, "FZTetris");
    TTF_Init();
    font = TTF_OpenFont("ocraext.ttf", HEIGHT / 30);
    if (font == nullptr) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
}

UiSdl::~UiSdl() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void UiSdl::clear_background() const {
    SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
    SDL_RenderClear(renderer);
}

void UiSdl::draw() const {
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
    draw_tetromino();
    draw_next_tetromino();

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
    const std::string next_str = "Next:   ";
    draw_text(TEXT_X, TEXT_HEIGHT * 3, TEXT_WIDTH, TEXT_HEIGHT, next_str, color);
    SDL_RenderPresent(renderer);
}

void UiSdl::handle_input() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        handle_left_key();
                        break;
                    case SDLK_RIGHT:
                        handle_right_key();
                        break;
                    case SDLK_SPACE:
                        handle_space_key();
                        break;
                    case SDLK_UP:
                        handle_up_key();
                        break;
                    case SDLK_DOWN:
                        handle_down_key();
                        break;
                    case SDLK_p:
                        handle_p_key();
                        break;
                    case SDLK_r:
                        handle_r_key();
                        break;
                    case SDLK_q:
                        handle_q_key();
                        break;
                    case SDLK_a:
                        handle_a_key();
                }
        }
    }
}

void UiSdl::draw_rect(const int x, const int y, const char c) const {
    static constexpr int RECT_SIZE = WIDTH / 40;
    static constexpr int BORDER_SIZE = 1;
    static SDL_Rect rect;
    rect.x = x * RECT_SIZE + BORDER_SIZE;
    rect.y = y * RECT_SIZE + BORDER_SIZE;
    rect.h = RECT_SIZE - 2 * BORDER_SIZE;
    rect.w = RECT_SIZE - 2 * BORDER_SIZE;
    switch (c) {
        case '#':
            SDL_SetRenderDrawColor(renderer, 90, 90, 90, 0);
            break;
        case 'I':
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

void UiSdl::draw_tetromino() const {
    for (int i = 0; i < table.tetromino->SIZE; ++i) {
        for (int j = 0; j < table.tetromino->SIZE; ++j) {
            if (table.tetromino->get_buffer(table.tetromino->buffer_index)[i][j] != Tetromino::EMPTY) {
                draw_rect(table.tetromino->get_x() + j + 1,
                          table.tetromino->get_y() + i + 1,
                          table.tetromino->get_buffer(table.tetromino->buffer_index)[i][j]);
            }
        }
    }
}

void UiSdl::draw_next_tetromino() const {
    for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
        for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
            draw_rect(table.next_tetromino->get_x() + j + 1,
                      table.next_tetromino->get_y() + i + 1,
                      Tetromino::EMPTY);
        }
    }
    for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
        for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
            if (table.next_tetromino->get_buffer(0)[i][j] != Tetromino::EMPTY) {
                draw_rect(table.next_tetromino->get_x() + j + 1,
                          table.next_tetromino->get_y() + i + 1,
                          table.next_tetromino->get_buffer(0)[i][j]);
            }
        }
    }
}

void UiSdl::draw_text(const int x, const int y, const int w, const int h,
        const std::string& message, const SDL_Color& color) const {
    static SDL_Rect rect;
    SDL_Surface *surface_message = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface_message);
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface_message);
}
