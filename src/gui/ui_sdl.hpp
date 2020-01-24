#pragma once

#include "ui.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Table;

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *surface_message;
extern SDL_Texture *texture;
extern SDL_Event event;
extern SDL_Rect rect;
extern TTF_Font *font;

// static constexpr int JOYSTICK_DEAD_ZONE = 8000;
extern SDL_Joystick* gGameController;

class UiSdl : public Ui {
public:
    UiSdl();

    ~UiSdl();

    void draw(const Table& table) const override;
    void update(Table& table) override;
    void clear_background() const override;

private:
    void draw_rect(const int x, const int y, const char c) const;
    void draw_tetromino(const Table& table) const;
    void draw_next_tetromino(const Table& table) const;
    void draw_text(const int x, const int y, const int w, const int h,
                   const std::string& message, const SDL_Color& color) const;
};
