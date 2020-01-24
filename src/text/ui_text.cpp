#include "ui_text.hpp"
#include "table.hpp"

#include <ncurses.h>

UiText::UiText() {
    init();
}

UiText::~UiText() {
    close();
}

void UiText::init() {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(Tetromino::COLOR_RED_IDX, COLOR_RED, COLOR_RED);
    init_pair(Tetromino::COLOR_GREEN_IDX, COLOR_GREEN, COLOR_GREEN);
    init_pair(Tetromino::COLOR_YELLOW_IDX, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(Tetromino::COLOR_BLUE_IDX, COLOR_BLUE, COLOR_BLUE);
    init_pair(Tetromino::COLOR_MAGENTA_IDX, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(Tetromino::COLOR_CYAN_IDX, COLOR_CYAN, COLOR_CYAN);
    init_pair(Tetromino::COLOR_WHITE_IDX, COLOR_WHITE, COLOR_WHITE);
}

void UiText::draw(const Table& table) const {
    for (int j = 0; j < table.WIDTH + 2; ++j) {
        mvaddch(0, j, HORIZONTAL_BORDER);
        mvaddch(table.HEIGHT + 1, j, HORIZONTAL_BORDER);
    }
    for (int i = 0; i < table.HEIGHT; ++i) {
        for (int j = 0; j < table.WIDTH; ++j) {
            const char c = table.buffer[i][j];
            if (c != Tetromino::EMPTY) {
                attron(COLOR_PAIR(Tetromino::COLOR_IDXS.at(c)));
                mvaddch(i + 1, j + 1, c);
                attroff(COLOR_PAIR(Tetromino::COLOR_IDXS.at(c)));
            } else {
                mvaddch(i + 1, j + 1, c);
            }
            mvaddch(i + 1, 0, VERTICAL_BORDER);
            mvaddch(i + 1, table.WIDTH + 1, VERTICAL_BORDER);
        }
    }
    draw_tetromino(table);
    draw_next_tetromino(table);
    mvprintw(0, table.WIDTH + 3, "Level: %d", table.get_level());
    mvprintw(1, table.WIDTH + 3, "Lines: %d", table.get_cleared_lines());
    mvprintw(2, table.WIDTH + 3, "Score: %d", table.get_score());
    mvprintw(4, table.WIDTH + 3, "Next:");
    refresh();
}

void UiText::draw_tetromino(const Table& table) const {
    attron(COLOR_PAIR(Tetromino::COLOR_IDXS.at(table.tetromino->get_block())));
    for (int i = 0; i < table.tetromino->SIZE; ++i) {
        for (int j = 0; j < table.tetromino->SIZE; ++j) {
            if (table.tetromino->buffer[i][j] == table.tetromino->get_block()) {
                mvaddch(table.tetromino->get_y() + i + 1,
                        table.tetromino->get_x() + j + 1,
                        table.tetromino->buffer[i][j]);
            }
        }
    }
    attroff(COLOR_PAIR(Tetromino::COLOR_IDXS.at(table.tetromino->get_block())));
}

void UiText::draw_next_tetromino(const Table& table) const {
    for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
        for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
            mvaddch(table.next_tetromino->get_y() + i + 1,
                    table.next_tetromino->get_x() + j + 1,
                    Tetromino::EMPTY);
        }
    }
    attron(COLOR_PAIR(Tetromino::COLOR_IDXS.at(table.next_tetromino->get_block())));
    for (int i = 0; i < table.next_tetromino->SIZE; ++i) {
        for (int j = 0; j < table.next_tetromino->SIZE; ++j) {
            if (table.next_tetromino->buffer[i][j] == table.next_tetromino->get_block()) {
                mvaddch(table.next_tetromino->get_y() + i + 1,
                        table.next_tetromino->get_x() + j + 1,
                        table.next_tetromino->buffer[i][j]);
            }
        }
    }
    attroff(COLOR_PAIR(Tetromino::COLOR_IDXS.at(table.next_tetromino->get_block())));
}

void UiText::update(Table& table) {
    int key = getch();
    flushinp();
    switch (key) {
        case KEY_LEFT:
            if (!end && !pause && table.is_empty_left_to_tetromino()) {
                table.tetromino->move_left();
            }
            break;
        case KEY_RIGHT:
            if (!end && !pause && table.is_empty_right_to_tetromino()) {
                table.tetromino->move_right();
            }
            break;
        case ' ':
            while (!end && !pause && table.is_empty_below_tetromino()) {
                table.tetromino->move_down();
            }
            break;
        case KEY_UP:
            if (!end && !pause) {
                table.rotate_tetromino();
            }
            break;
        case KEY_DOWN:
            if (!end && !pause && table.is_empty_below_tetromino()) {
                table.tetromino->move_down();
            }
            break;
        case 'p':
            pause = !pause;
            break;
        case 'r':
            if (wait_for_restart) {
                table.init();
                pause = false;
                end = false;
                wait_for_restart = false;
            }
            break;
        case 'q':
            quit = true;
            break;
    }
}

void UiText::close() {
    endwin();
}
