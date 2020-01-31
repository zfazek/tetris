#pragma once

#include <array>
#include <map>
#include <memory>
#include <vector>

class Tetromino {
public:
    static constexpr int SIZE = 4;
    typedef std::array<std::array<char, SIZE>, SIZE> BufferT;

    Tetromino();
    virtual ~Tetromino() = default;
    void clear_buffer();
    void move_down();
    void move_left();
    void move_right();
    int get_x() const;
    void set_x(const int x_);
    int get_y() const;
    void set_y(const int y_);
    virtual char get_block() const = 0;
    virtual BufferT get_buffer(const int buffer_index) const = 0;
    virtual int get_buffers_size() const = 0;

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

private:
    int x;
    int y;

};

typedef std::unique_ptr<Tetromino> TetrominoPtr;
