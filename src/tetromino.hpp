#pragma once

#include <array>
#include <map>
#include <memory>

class Tetromino;
typedef std::unique_ptr<Tetromino> TetrominoPtr;

class Tetromino {
public:
    virtual ~Tetromino() = default;

    virtual TetrominoPtr rotated() = 0;
    virtual char get_block() const = 0;

    static constexpr int SIZE = 4;
    typedef std::array<std::array<char, SIZE>, SIZE> BufferT;

    int x;
    int y;

    int buffer_index = 0;
    BufferT buffer;

    static constexpr char EMPTY = ' ';

    static constexpr int COLOR_BLACK_IDX = 0;
    static constexpr int COLOR_RED_IDX = 1;
    static constexpr int COLOR_GREEN_IDX = 2;
    static constexpr int COLOR_YELLOW_IDX = 3;
    static constexpr int COLOR_BLUE_IDX = 4;
    static constexpr int COLOR_MAGENTA_IDX = 5;
    static constexpr int COLOR_CYAN_IDX = 6;
    static constexpr int COLOR_WHITE_IDX = 7;

    static const std::map<char, int> COLOR_IDXS;
};

template <class Derived>
class TetrominoBase : public Tetromino {
public:
    TetrominoBase()
            : Tetromino()
            , derived(*static_cast<Derived*>(this)) {
        buffer = derived.BUFFERS[buffer_index];
    }

    TetrominoBase(const TetrominoBase& other)
            : Tetromino(other)
            , derived(*static_cast<Derived*>(this)) {
    }

    TetrominoPtr rotated() {  // for reference, see https://www.retrogames.cz/play_1030-NES.php
        TetrominoPtr rotated_tetromino = std::make_unique<Derived>(derived);
        rotated_tetromino->buffer_index = (buffer_index + 1) % derived.BUFFERS.size();
        rotated_tetromino->buffer = derived.BUFFERS[buffer_index];
        return rotated_tetromino;
    }

    Derived& derived;
};
