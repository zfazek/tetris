#include "tetromino.hpp"

const std::map<char, int> Tetromino::COLOR_IDXS = {
    {'#', COLOR_BLACK_IDX},
    {'X', COLOR_CYAN_IDX},
    {'O', COLOR_YELLOW_IDX},
    {'T', COLOR_MAGENTA_IDX},
    {'J', COLOR_BLUE_IDX},
    {'L', COLOR_WHITE_IDX},
    {'S', COLOR_GREEN_IDX},
    {'Z', COLOR_RED_IDX},
};
