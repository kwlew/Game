// File created by kwlew on 2026-12-09 @ 2:18 AM

#include "game/logger.hpp"
#include "game/engine.hpp"
#include "game/config.hpp"

#include <game/colors.hpp>

#include <raylib.h>

int main() {
    game::Engine engine;

    // Keep game INFO logs, but suppress Raylib INFO startup noise.
    game::Logger::init(LOG_INFO, LOG_WARNING);

    auto config = game::defaultConfig;
    game::Logger::log(LOG_INFO, "Loading default config...");

    config.window.width = 800;
    config.window.height = 600;
    config.window.targetFPS = 120;
    config.window.showFPS = true;

    game::Logger::log(
        LOG_INFO,
        "Config initialized (%dx%d, %d FPS)",
        config.window.width,
        config.window.height,
        config.window.targetFPS
    );

    if (!engine.initialize(config.window, "Learning Raylib")) {
        return -1;
    }

    while (engine.running()) {
        engine.drawFrame([&] {
            ClearBackground(game::colors::menuBackground);

            if (config.window.showFPS) {
                engine.debugFPS();
            }
        });
    }

    engine.shutdown();
}
