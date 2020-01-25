#include "ui.hpp"

Ui::Ui() {
    game_state = GameState::GAME;
}

void Ui::handle_left_key() {
    if (game_state == GameState::GAME && table.is_empty_left_to_tetromino()) {
        table.tetromino->move_left();

    }
}
void Ui::handle_right_key() {
    if (game_state == GameState::GAME && table.is_empty_right_to_tetromino()) {
        table.tetromino->move_right();
    }
}
void Ui::handle_up_key() {
    if (game_state == GameState::GAME) {
        table.rotate_tetromino();
    }
}
void Ui::handle_down_key() {
    if (game_state == GameState::GAME && table.is_empty_below_tetromino()) {
        table.tetromino->move_down();
    }
}
void Ui::handle_space_key() {
    while (game_state == GameState::GAME && table.is_empty_below_tetromino()) {
        table.tetromino->move_down();
    }
}
void Ui::handle_p_key() {
    if (game_state == GameState::QUIT) {
        game_state = GameState::GAME;
    } else if (game_state == GameState::GAME) {
        game_state = GameState::PAUSE;
    } else if (game_state == GameState::PAUSE) {
        game_state = GameState::GAME;
    }
}
void Ui::handle_r_key() {
    if (game_state == GameState::WAIT_FOR_RESTART) {
        table.init();
        game_state = GameState::GAME;
    }
}
void Ui::handle_q_key() {
    game_state = GameState::QUIT;
}
