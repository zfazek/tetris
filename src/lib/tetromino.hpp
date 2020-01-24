#pragma once

#include <map>
#include <memory>

class Tetromino {
public:
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

    static constexpr int SIZE = 4;
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

    char buffer[SIZE][SIZE];

private:
    int x;
    int y;

};

typedef std::unique_ptr<Tetromino> TetrominoPtr;

