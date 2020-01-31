#pragma once

#include "ui.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

class UiSdl : public Ui {
public:
    UiSdl();

    ~UiSdl();

    void draw() const override;
    void handle_input() override;
    void clear_background() const override;

private:
    void draw_rect(const int x, const int y, const char c) const;
    void draw_tetromino() const;
    void draw_next_tetromino() const;
    void draw_text(const int x, const int y, const int w, const int h,
                   const std::string& message, const SDL_Color& color) const;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    TTF_Font *font;
};
