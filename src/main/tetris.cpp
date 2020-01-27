#include "mainloop.hpp"
#include "ui_text.hpp"

#include <chrono>
#include <thread>

int main() {
    UiPtr gui = std::make_shared<UiText>();

    while (gui->game_state != GameState::QUIT) {
        mainloop(gui);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
