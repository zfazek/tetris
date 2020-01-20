#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class ITetromino : public TetrominoBase<ITetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'X';
};

const std::vector<Tetromino::BufferT> ITetromino::BUFFERS {
    // TODO: check
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {BLOCK, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
    }},
};
