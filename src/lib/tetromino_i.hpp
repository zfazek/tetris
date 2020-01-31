#pragma once

#include "tetromino.hpp"

#include <vector>

class ITetromino : public Tetromino {
public:
    char get_block() const override {
        return BLOCK;
    }

    BufferT get_buffer(const int buffer_index) const {
        return BUFFERS[buffer_index];
    }

    int get_buffers_size() const {
        return BUFFERS.size();
    }

private:
    static constexpr char BLOCK = 'I';
    static const std::vector<BufferT> BUFFERS;
};
