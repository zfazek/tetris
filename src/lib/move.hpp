#pragma once

#include "tetromino.hpp"

class Move {
public:
    TetrominoPtr tetromino;
    int x;
    int buffer_index;
};
