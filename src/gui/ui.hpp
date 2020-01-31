#pragma once

#include "ai_mode.hpp"
#include "game_state.hpp"
#include "move.hpp"
#include "table.hpp"

#include <memory>

class Ui {
public:
    Ui();
    virtual ~Ui() = default;
    virtual void draw() const = 0;
    virtual void handle_input() = 0;
    virtual void clear_background() const {}
    bool update(const float elapsed_time);
    void handle_left_key();
    void handle_right_key();
    void handle_up_key();
    void handle_down_key();
    void handle_space_key();
    void handle_p_key();
    void handle_r_key();
    void handle_q_key();
    void handle_a_key();
    void make_ai_move();

    Table table;
    Move ai_move;
    GameState game_state;
    AImode ai_mode;

private:
    void add_moves(std::vector<Move>& moves) const;
};

typedef std::shared_ptr<Ui> UiPtr;
