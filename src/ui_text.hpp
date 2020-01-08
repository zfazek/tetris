#pragma once

#include "ui.hpp"

class Table;

class UiText : public Ui {
public:
    UiText();
    ~UiText() override;
    void draw(const Table& table) const override;
    void update(Table& table) override;

private:
    void init();
    void close();
    void draw_tetromino(const Table& table) const;
    void draw_next_tetromino(const Table& table) const;

    static constexpr char VERTICAL_BORDER = '|';
    static constexpr char HORIZONTAL_BORDER = '=';
};
