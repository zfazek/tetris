#include "table.hpp"
#include "tetromino_i.hpp"
#include "tetromino_j.hpp"
#include "tetromino_l.hpp"
#include "tetromino_o.hpp"
#include "tetromino_s.hpp"
#include "tetromino_t.hpp"
#include "tetromino_z.hpp"

#include <cstdlib>
#include <ctime>

Table::Table() {
    srand(time(nullptr));
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
        tetromino->set_x(WIDTH / 2 - tetromino->SIZE / 2);
        tetromino->set_y(0);
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
    next_tetromino->set_x(WIDTH + 2);
    next_tetromino->set_y(4);
}

bool Table::rotate_tetromino() {
    const int new_buffer_index = (tetromino->buffer_index + 1) % tetromino->get_buffers_size();
    for (int i = 0; i < tetromino->SIZE; ++i) {
        for (int j = 0; j < tetromino->SIZE; ++j) {
            if (tetromino->get_buffer(new_buffer_index)[i][j] != Tetromino::EMPTY) {
                if (buffer[tetromino->get_y() + i][tetromino->get_x() + j] != Tetromino::EMPTY) {
                    return false;
                }
                if (tetromino->get_x() + j < 0) {
                    return false;
                }
                if (tetromino->get_x() + j >= WIDTH) {
                    return false;
                }
                if (tetromino->get_y() + i < 0) {
                    return false;
                }
                if (tetromino->get_y() + i >= HEIGHT) {
                    return false;
                }
            }
        }
    }
    tetromino->buffer_index = new_buffer_index;
    return true;
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
            if (tetromino->get_buffer(tetromino->buffer_index)[i][j] != Tetromino::EMPTY) {
                if (tetromino->get_y() + i >= HEIGHT - 1) {
                    return false;
                }
                if (buffer[tetromino->get_y() + i + 1][tetromino->get_x() + j] != Tetromino::EMPTY) {
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
            if (tetromino->get_buffer(tetromino->buffer_index)[i][j] != Tetromino::EMPTY) {
                if (tetromino->get_x() + j >= WIDTH - 1) {
                    return false;
                }
                if (buffer[tetromino->get_y() + i][tetromino->get_x() + j + 1] != Tetromino::EMPTY) {
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
            if (tetromino->get_buffer(tetromino->buffer_index)[i][j] != Tetromino::EMPTY) {
                if (tetromino->get_x() + j <= 0) {
                    return false;
                }
                if (buffer[tetromino->get_y() + i][tetromino->get_x() + j - 1] != Tetromino::EMPTY) {
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
            if (tetromino->get_buffer(tetromino->buffer_index)[i][j] != Tetromino::EMPTY) {
                buffer[tetromino->get_y() + i][tetromino->get_x() + j] = tetromino->get_buffer(tetromino->buffer_index)[i][j];
            }
        }
    }
}

bool Table::update(const float elapsed_time) {
    delta_time += elapsed_time;
    if (delta_time < max_delta_time / (1 + get_level() * 0.05)) {
        return false;
    }
    dirty = true;
    delta_time = 0.0f;
    if (is_empty_below_tetromino()) {
        tetromino->move_down();
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
