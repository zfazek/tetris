#include "tetromino.hpp"

Tetromino::Tetromino() {
}

int Tetromino::get_x() const {
    return x;
}

void Tetromino::set_x(const int x_) {
    x = x_;
}

int Tetromino::get_y() const {
    return y;
}

void Tetromino::set_y(const int y_) {
    y = y_;
}

void Tetromino::move_down() {
    ++y;
}

void Tetromino::move_left() {
    --x;
}

void Tetromino::move_right() {
    ++x;
}

const std::map<char, int> Tetromino::COLOR_IDXS = {
    {'#', COLOR_BLACK_IDX},
    {'I', COLOR_CYAN_IDX},
    {'O', COLOR_YELLOW_IDX},
    {'T', COLOR_MAGENTA_IDX},
    {'J', COLOR_BLUE_IDX},
    {'L', COLOR_WHITE_IDX},
    {'S', COLOR_GREEN_IDX},
    {'Z', COLOR_RED_IDX},
};
