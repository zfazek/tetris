#include "table.hpp"
#include "i_tetromino.hpp"
#include "j_tetromino.hpp"
#include "l_tetromino.hpp"
#include "o_tetromino.hpp"
#include "s_tetromino.hpp"
#include "t_tetromino.hpp"
#include "z_tetromino.hpp"

#include <cstdlib>
#include <ctime>
#include <stdio.h>

Table::Table() {
    srand(time(NULL));
    init();
}

void Table::init() {
    clear_buffer();
    cleared_lines = 0;
    score = 0;
    new_tetromino();
    new_tetromino();
}

void Table::new_tetromino() {
    if (next_tetromino) {
        tetromino = std::move(next_tetromino);
        tetromino->x = WIDTH / 2 - tetromino->SIZE / 2;
        tetromino->y = 0;
    }
    const int tetromino_idx = rand() % 7;
    switch (tetromino_idx) {
        case 0:
            next_tetromino = std::make_unique<ITetromino>();
            break;
        case 1:
            next_tetromino = std::make_unique<OTetromino>();
            break;
        case 2:
            next_tetromino = std::make_unique<TTetromino>();
            break;
        case 3:
            next_tetromino = std::make_unique<JTetromino>();
            break;
        case 4:
            next_tetromino = std::make_unique<LTetromino>();
            break;
        case 5:
            next_tetromino = std::make_unique<STetromino>();
            break;
        case 6:
            next_tetromino = std::make_unique<ZTetromino>();
            break;
    }
    next_tetromino->x = 12;
    next_tetromino->y = 4;
}

void Table::rotate_tetromino() {
    TetrominoPtr rotated_tetromino = tetromino->rotate();
    if (!would_collide(rotated_tetromino->buffer)) {
        tetromino = std::move(rotated_tetromino);
    }
}

bool Table::would_collide(const Tetromino::BufferT& tmp_buffer) {
    for (int i = 0; i < Tetromino::SIZE; ++i) {
        for (int j = 0; j < Tetromino::SIZE; ++j) {
            if (tmp_buffer[i][j] != Tetromino::EMPTY) {
                if (buffer[tetromino->y + i][tetromino->x + j] != Tetromino::EMPTY) {
                    return true;
                }
                if (tetromino->x + j < 0) {
                    return true;
                }
                if (tetromino->x + j >= WIDTH) {
                    return true;
                }
                if (tetromino->y + i < 0) {
                    return true;
                }
                if (tetromino->y + i >= HEIGHT) {
                    return true;
                }
            }
        }
    }
    return false;
}


void Table::clear_buffer() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            buffer[i][j] = Tetromino::EMPTY;
        }
    }
}

bool Table::is_empty_below_tetromino() const {
    for (int i = 0; i < tetromino->SIZE; ++i) {
        for (int j = 0; j < tetromino->SIZE; ++j) {
            if (tetromino->buffer[i][j] == tetromino->get_block()) {
                if (tetromino->y + i >= HEIGHT - 1) {
                    return false;
                }
                if (buffer[tetromino->y + i + 1][tetromino->x + j] != Tetromino::EMPTY) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Table::is_empty_right_to_tetromino() const {
    for (int i = 0; i < tetromino->SIZE; ++i) {
        for (int j = 0; j < tetromino->SIZE; ++j) {
            if (tetromino->buffer[i][j] == tetromino->get_block()) {
                if (tetromino->x + j >= WIDTH - 1) {
                    return false;
                }
                if (buffer[tetromino->y + i][tetromino->x + j + 1] != Tetromino::EMPTY) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Table::is_empty_left_to_tetromino() const {
    for (int i = 0; i < tetromino->SIZE; ++i) {
        for (int j = 0; j < tetromino->SIZE; ++j) {
            if (tetromino->buffer[i][j] == tetromino->get_block()) {
                if (tetromino->x + j <= 0) {
                    return false;
                }
                if (buffer[tetromino->y + i][tetromino->x + j - 1] != Tetromino::EMPTY) {
                    return false;
                }
            }
        }
    }
    return true;
}

int Table::get_level() const {
    return cleared_lines / 10;
}

int Table::get_cleared_lines() const {
    return cleared_lines;
}

int Table::get_score() const {
    return score;
}

void Table::remove_completed_lines() {
    int removed_lines = 0;
    for (int i = HEIGHT - 1; i >= 0; --i) {
        bool full = true;
        for (int j = 0; j < WIDTH; ++j) {
            if (buffer[i][j] == Tetromino::EMPTY) {
                full = false;
                break;
            }
        }
        if (full) {
            ++removed_lines;
            for (int k = i - 1; k >= 0; --k) {
                for (int j = 0; j < WIDTH; ++j) {
                    buffer[k + 1][j] = buffer[k][j];
                }
            }
            ++i;
        }
    }
    if (removed_lines > 0 && removed_lines < 5) {
        const int level = get_level();
        cleared_lines += removed_lines;
        score += scores[removed_lines - 1] * (level + 1);
    }
}

void Table::put_tetromino() {
    for (int i = 0; i < tetromino->SIZE; ++i) {
        for (int j = 0; j < tetromino->SIZE; ++j) {
            if (tetromino->buffer[i][j] == tetromino->get_block()) {
                buffer[tetromino->y + i][tetromino->x + j] = tetromino->buffer[i][j];
            }
        }
    }
}

bool Table::update(const float elapsed_time) {
    delta_time += elapsed_time;
    if (delta_time < max_delta_time * 1 / (1 + get_level() * 0.1)) {
        return false;
    }
    delta_time = 0.0f;
    if (is_empty_below_tetromino()) {
        ++tetromino->y;
    } else {
        put_tetromino();
        remove_completed_lines();
        new_tetromino();
        if (!is_empty_below_tetromino()) {
            return true;
        }
    }
    return false;
}
