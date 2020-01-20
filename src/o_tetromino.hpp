#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class OTetromino : public TetrominoBase<OTetromino> {
public:
    char get_block() const override {
        return BLOCK;
    }

    static const std::vector<BufferT> BUFFERS;

private:
    static constexpr char BLOCK = 'O';
};

const std::vector<Tetromino::BufferT> OTetromino::BUFFERS {
    {{
        {EMPTY, EMPTY, EMPTY, EMPTY},
        {BLOCK, BLOCK, EMPTY, EMPTY},
        {BLOCK, BLOCK, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY},
    }},
};
