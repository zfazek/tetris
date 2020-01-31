#pragma once

#include "tetromino.hpp"

class ZTetromino : public Tetromino {
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
    static constexpr char BLOCK = 'Z';
    static const std::vector<BufferT> BUFFERS;
};
