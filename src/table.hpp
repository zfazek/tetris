#pragma once

#include <array>

#include "tetromino.hpp"

class Table {
public:
    Table();
    void init();
    void new_tetromino();
    void rotate_tetromino();
    bool collides(const Tetromino::BufferT& tmp_buffer);
    void clear_buffer();
    bool update(float elapsed_time);
    bool is_empty_below_tetromino() const;
    bool is_empty_right_to_tetromino() const;
    bool is_empty_left_to_tetromino() const;
    int get_level() const;
    int get_cleared_lines() const;
    int get_score() const;

    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 24;

    std::array<std::array<char, WIDTH>, HEIGHT> buffer;

    TetrominoPtr tetromino;
    TetrominoPtr next_tetromino;

private:
    float max_delta_time = 0.3f;
    float delta_time = 0.0f;
    void remove_completed_lines();
    void put_tetromino();

    int cleared_lines = 0;
    int score = 0;
    int scores[4] = {40, 100, 300, 1200};
};
