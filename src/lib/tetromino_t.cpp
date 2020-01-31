#include "tetromino_t.hpp"

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
