#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class TTetromino : public TetrominoBase<TTetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'T';
};

const std::vector<Tetromino::BufferT> TTetromino::BUFFERS {
    // TODO: check
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, BLOCK},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, BLOCK, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
