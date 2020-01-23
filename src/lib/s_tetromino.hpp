#pragma once

#include "tetromino.hpp"

class STetromino : public Tetromino {
public:
    STetromino() {
        buffer[1][2] = BLOCK;
        buffer[1][3] = BLOCK;
        buffer[2][1] = BLOCK;
        buffer[2][2] = BLOCK;
    }

    char get_block() const override {
        return BLOCK;
    }

private:
    static constexpr char BLOCK = 'S';
};
