#pragma once

#include "ui.hpp"

class UiText : public Ui {
public:
    UiText();
    ~UiText() override;
    void draw() const override;
    void handle_input() override;

private:
    void init();
    void close();
    void draw_tetromino() const;
    void draw_next_tetromino() const;

    static constexpr char VERTICAL_BORDER = '|';
    static constexpr char HORIZONTAL_BORDER = '=';
};
