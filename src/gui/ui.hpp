#pragma once

#include "game_state.hpp"
#include "table.hpp"

#include <memory>

class Ui {
public:
    Ui();
    virtual ~Ui() = default;
    virtual void draw() const = 0;
    virtual void update() = 0;
    virtual void clear_background() const {}
    void handle_left_key();
    void handle_right_key();
    void handle_up_key();
    void handle_down_key();
    void handle_space_key();
    void handle_p_key();
    void handle_r_key();
    void handle_q_key();

    Table table;
    GameState game_state;
};

typedef std::shared_ptr<Ui> UiPtr;
