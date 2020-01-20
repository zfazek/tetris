#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class LTetromino : public TetrominoBase<LTetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'L';
};

const std::vector<Tetromino::BufferT> LTetromino::BUFFERS {
    // TODO: check
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, EMPTY, BLOCK},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
