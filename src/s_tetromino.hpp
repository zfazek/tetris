#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class STetromino : public TetrominoBase<STetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'S';
};

const std::vector<Tetromino::BufferT> STetromino::BUFFERS {
    // TODO: check
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLOCK, BLOCK},
        {EMPTY, BLOCK, BLOCK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
    {{
        {EMPTY, EMPTY, BLOCK, EMPTY},
        {EMPTY, EMPTY, BLOCK, BLOCK},
        {EMPTY, EMPTY, EMPTY, BLOCK},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
