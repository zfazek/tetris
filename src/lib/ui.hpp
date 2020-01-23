#pragma once

#include <memory>

class Table;

class Ui {
public:
    virtual ~Ui() = default;
    virtual void draw(const Table& table) const = 0;
    virtual void update(Table& table) = 0;

    bool end = false;
    bool quit = false;
    bool pause = false;
    bool wait_for_restart = false;
};

typedef std::unique_ptr<Ui> UiPtr;
