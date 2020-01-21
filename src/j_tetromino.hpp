#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class JTetromino : public TetrominoBase<JTetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'J';
};

const std::vector<Tetromino::BufferT> JTetromino::BUFFERS {
    // TODO: check
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, BLOCK},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
