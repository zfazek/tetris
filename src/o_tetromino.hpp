#pragma once

#include <vector>

#include "tetromino.hpp"

class OTetromino : public TetrominoBase<OTetromino> {
public:
    static const std::vector<BufferT> BUFFERS;
    static constexpr char BLOCK = 'O';
};

const std::vector<Tetromino::BufferT> OTetromino::BUFFERS {
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
