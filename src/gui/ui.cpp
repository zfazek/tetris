#include "ui.hpp"
#include "tetromino_i.hpp"
#include "tetromino_j.hpp"
#include "tetromino_l.hpp"
#include "tetromino_o.hpp"
#include "tetromino_s.hpp"
#include "tetromino_t.hpp"
#include "tetromino_z.hpp"

#include <cstdlib>
#include <ctime>

Ui::Ui() {
    game_state = GameState::GAME;
    srand(time(nullptr));
}

void Ui::handle_left_key() {
    if (game_state == GameState::GAME && table.is_empty_left_to_tetromino()) {
        table.tetromino->move_left();
        table.dirty = true;
    }
}

void Ui::handle_right_key() {
    if (game_state == GameState::GAME && table.is_empty_right_to_tetromino()) {
        table.tetromino->move_right();
        table.dirty = true;
    }
}

void Ui::handle_up_key() {
    if (game_state == GameState::GAME) {
        table.rotate_tetromino();
        table.dirty = true;
    }
}

void Ui::handle_down_key() {
    if (game_state == GameState::GAME && table.is_empty_below_tetromino()) {
        table.tetromino->move_down();
        table.dirty = true;
    }
}

void Ui::handle_space_key() {
    while (game_state == GameState::GAME && table.is_empty_below_tetromino()) {
        table.tetromino->move_down();
    }
    table.dirty = true;
}

void Ui::handle_p_key() {
    if (game_state == GameState::GAME) {
        game_state = GameState::PAUSE;
        table.dirty = false;
    } else if (game_state == GameState::PAUSE) {
        game_state = GameState::GAME;
        table.dirty = true;
    }
}

void Ui::handle_r_key() {
    if (game_state == GameState::WAIT_FOR_RESTART) {
        table.init();
        game_state = GameState::GAME;
        table.dirty = true;
        ai_mode = AImode::NONE;
    }
}

void Ui::handle_q_key() {
    game_state = GameState::QUIT;
}

void Ui::handle_a_key() {
    if (ai_mode == AImode::NONE) {
        ai_mode = AImode::READY;
    } else {
        ai_mode = AImode::NONE;
    }
}

void Ui::add_moves(std::vector<Move>& moves) const {
    for (int x = -1; x < table.WIDTH; ++x) {
        for (int i = 0; i < table.tetromino->get_buffers_size(); ++i) {
            if (table.is_tetromino_placeable(x, 0, i)) {
                moves.push_back({x, i});
            }
        }
    }
}

void Ui::make_ai_move() {
    if (ai_mode == AImode::READY) {
        std::vector<Move> moves;
        add_moves(moves);
        const int move_idx = rand() % moves.size();
        ai_move.x = moves[move_idx].x;
        ai_move.buffer_index = moves[move_idx].buffer_index;
        ai_mode = AImode::IN_PROGRESS;
    } else if (ai_mode == AImode::IN_PROGRESS) {
        if (table.tetromino->buffer_index == ai_move.buffer_index) {
            if (table.tetromino->get_x() == ai_move.x) {
                handle_space_key();
                ai_mode = AImode::READY;
            } else if (table.tetromino->get_x() < ai_move.x) {
                handle_right_key();
            } else if (table.tetromino->get_x() > ai_move.x) {
                handle_left_key();
            }
        } else {
            table.tetromino->buffer_index =
                (table.tetromino->buffer_index + 1) % table.tetromino->get_buffers_size();
        }
    }
}

bool Ui::update(const float elapsed_time) {
    table.delta_time += elapsed_time;
    if (table.delta_time < table.max_delta_time / (1 + table.get_level() * 0.05)) {
        return false;
    }
    table.dirty = true;
    table.delta_time = 0.0f;
    if (ai_mode != AImode::NONE) {
        make_ai_move();
    }
    if (table.is_empty_below_tetromino()) {
        table.tetromino->move_down();
    } else {
        table.put_tetromino();
        table.remove_completed_lines();
        table.new_tetromino();
        if (!table.is_empty_below_tetromino()) {
            return true;
        }
    }
    return false;
}
