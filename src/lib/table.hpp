#pragma once

#include "tetromino.hpp"

class Table {
public:
    Table();
    void init();
    void new_tetromino();
    bool rotate_tetromino();
    void clear_buffer();
    bool is_empty_below_tetromino() const;
    bool is_empty_right_to_tetromino() const;
    bool is_empty_left_to_tetromino() const;
    bool is_tetromino_placeable(const int x, const int y, const int buffer_index) const;
    int get_level() const;
    int get_cleared_lines() const;
    int get_score() const;
    void remove_completed_lines();
    void put_tetromino();

    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 24;

    char buffer[HEIGHT][WIDTH];
    TetrominoPtr tetromino;
    TetrominoPtr next_tetromino;
    bool dirty = true;
    float delta_time = 0.0f;
    float max_delta_time = 0.3f;

    int cleared_lines = 0;
    int score = 0;
    int scores[4] = {40, 100, 300, 1200};
};
