#include "mainloop.hpp"

#include <chrono>

std::chrono::system_clock::time_point prev_time = std::chrono::system_clock::now();

void mainloop(UiPtr gui) {
    gui->clear_background();
    gui->draw();
    if (gui->game_state == GameState::GAME) {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        const float elapsed_sec =
            std::chrono::duration<float, std::milli>(current_time - prev_time).count() / 1000.0f;
        prev_time = current_time;
        const bool end = gui->table.update(elapsed_sec);
        if (end) {
            gui->game_state = GameState::WAIT_FOR_RESTART;
        }
    }
    gui->update();
}
