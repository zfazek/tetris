#include "mainloop.hpp"
#include "ui_text.hpp"

int main() {
    Table table;
    UiPtr gui = std::make_unique<UiText>();

    while (gui->game_state != GameState::QUIT) {
        mainloop(gui, table);
    }
}
