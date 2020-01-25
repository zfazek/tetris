#include "mainloop.hpp"
#include "ui_sdl.hpp"

int main() {
    UiPtr gui = std::make_shared<UiSdl>();

    while (gui->game_state != GameState::QUIT) {
        mainloop(gui);
    }
}

