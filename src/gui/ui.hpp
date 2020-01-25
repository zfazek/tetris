#pragma once

#include "game_state.hpp"
#include "table.hpp"

#include <memory>

class Ui {
public:
    Ui();
    virtual ~Ui() = default;
    virtual void draw(const Table& table) const = 0;
    virtual void update(Table& table) = 0;
    virtual void clear_background() const {}
    void handle_left_key(Table& table);
    void handle_right_key(Table& table);
    void handle_up_key(Table& table);
    void handle_down_key(Table& table);
    void handle_space_key(Table& table);
    void handle_p_key(Table& table);
    void handle_r_key(Table& table);
    void handle_q_key(Table& table);

    GameState game_state;
};

typedef std::shared_ptr<Ui> UiPtr;
