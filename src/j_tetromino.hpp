#pragma once

#include <vector>

#include "tetromino.hpp"

class JTetromino : public TetrominoBase<JTetromino> {
public:
    static const std::vector<BufferT> BUFFERS;
    static constexpr char BLOCK = 'J';
};

const std::vector<Tetromino::BufferT> JTetromino::BUFFERS {
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {BLOCK, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {BLOCK, EMPTY, EMPTY, EMPTY},
        {BLOCK, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {BLOCK, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
