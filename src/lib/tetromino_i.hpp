#pragma once

#include "tetromino.hpp"

class ITetromino : public Tetromino {
public:
    ITetromino() {
        for (int i = 0; i < SIZE; ++i) {
            buffer[1][i] = BLOCK;
        }
    }

    char get_block() const override {
        return BLOCK;
    }

private:
    static constexpr char BLOCK = 'X';
};
