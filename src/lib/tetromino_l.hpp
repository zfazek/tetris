#pragma once

#include "tetromino.hpp"

class LTetromino : public Tetromino {
public:
    LTetromino() {
        buffer[1][1] = BLOCK;
        buffer[1][2] = BLOCK;
        buffer[1][3] = BLOCK;
        buffer[2][1] = BLOCK;
    }

    char get_block() const override {
        return BLOCK;
    }

private:
    static constexpr char BLOCK = 'L';
};
