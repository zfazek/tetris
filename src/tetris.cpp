#include "table.hpp"
#include "ui.hpp"
#include "ui_text.hpp"

#include <chrono>
#include <thread>

int main() {
    Table table;
    UiPtr gui = std::make_unique<UiText>();

    std::chrono::system_clock::time_point prev_time = std::chrono::system_clock::now();
    while (!gui->quit) {
        gui->draw(table);
        if (!gui->pause) {
            std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
            const float elapsed_sec =
                std::chrono::duration<float, std::milli>(current_time - prev_time).count() / 1000.0f;
            prev_time = current_time;
            if (!gui->end) {
                gui->end = table.update(elapsed_sec);
                if (gui->end) {
                    gui->wait_for_restart = true;
                }
            }
        }
        gui->update(table);
    }
    puts("");
}
