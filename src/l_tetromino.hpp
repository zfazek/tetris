#pragma once

#include <memory>
#include <vector>

#include "tetromino.hpp"

class LTetromino : public Tetromino {
public:
    LTetromino() {
        buffer = BUFFERS[buffer_index];
    }

    char get_block() const override {
        return BLOCK;
    }

    TetrominoPtr rotate() override {
        TetrominoPtr rotated_tetromino = std::make_unique<LTetromino>(*this);
        rotated_tetromino->buffer_index = (buffer_index + 1) % BUFFERS.size();
        rotated_tetromino->buffer = BUFFERS[rotated_tetromino->buffer_index];
        return rotated_tetromino;
    }

private:
    static constexpr char BLOCK = 'L';
    static const std::vector<BufferT> BUFFERS;
};

const std::vector<Tetromino::BufferT> LTetromino::BUFFERS {
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
