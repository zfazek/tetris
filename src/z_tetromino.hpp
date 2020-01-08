#pragma once

#include "tetromino.hpp"

class ZTetromino : public Tetromino {
public:
    ZTetromino() {
        buffer[1][1] = BLOCK;
        buffer[1][2] = BLOCK;
        buffer[2][2] = BLOCK;
        buffer[2][3] = BLOCK;
    }

    char get_block() const override {
        return BLOCK;
    }

private:
    static constexpr char BLOCK = 'Z';
};
