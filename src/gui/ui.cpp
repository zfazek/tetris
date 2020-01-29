#include "ui.hpp"

Ui::Ui() {
    game_state = GameState::GAME;
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
    }
}
void Ui::handle_q_key() {
    game_state = GameState::QUIT;
}
