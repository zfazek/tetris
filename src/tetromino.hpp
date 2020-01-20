#pragma once

#include <array>
#include <map>
#include <memory>

class Tetromino;
typedef std::unique_ptr<Tetromino> TetrominoPtr;

class Tetromino {
public:
    static constexpr int SIZE = 4;
    typedef std::array<std::array<char, SIZE>, SIZE> BufferT;

    Tetromino();
    virtual ~Tetromino() = default;
    virtual char get_block() const = 0;
    virtual TetrominoPtr rotate() = 0;

    int x;
    int y;
    int buffer_index = 0;

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

    BufferT buffer;
};
