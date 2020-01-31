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
        ai_mode = false;
    }
}

void Ui::handle_q_key() {
    game_state = GameState::QUIT;
}

void Ui::handle_a_key() {
    ai_mode = !ai_mode;
}

void Ui::add_move(std::vector<Move>& moves, TetrominoPtr tetromino) const {
    for (int x = -1; x < table.WIDTH; ++x) {
    }
}

void Ui::make_ai_move() {
    std::vector<Move> moves;
    add_move(moves, std::make_unique<ITetromino>());
    const int move = rand() % 4;
    switch (move) {
        case 0:
            handle_left_key();
            break;
        case 1:
            handle_right_key();
            break;
        case 2:
            handle_up_key();
            break;
        case 3:
            handle_down_key();
            break;
    }
}
