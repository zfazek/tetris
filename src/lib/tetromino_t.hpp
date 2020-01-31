#pragma once

#include "tetromino.hpp"

class TTetromino : public Tetromino {
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
    static constexpr char BLOCK = 'T';
    static const std::vector<BufferT> BUFFERS;
};
