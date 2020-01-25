#include "mainloop.hpp"
#include "ui_text.hpp"

int main() {
    UiPtr gui = std::make_shared<UiText>();

    while (gui->game_state != GameState::QUIT) {
        mainloop(gui);
    }
}
