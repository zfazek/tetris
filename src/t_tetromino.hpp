#pragma once

#include <vector>

#include "tetromino.hpp"

class TTetromino : public TetrominoBase<TTetromino> {
public:
    static const std::vector<BufferT> BUFFERS;
    static constexpr char BLOCK = 'T';
};

const std::vector<Tetromino::BufferT> TTetromino::BUFFERS {
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {BLOCK, BLOCK, BLOCK, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {BLOCK, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {BLOCK, BLOCK, EMPTY, EMPTY},
        {EMPTY, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
