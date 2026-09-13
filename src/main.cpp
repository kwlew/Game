// File created by kwlew on 2026-12-09 @ 2:18 AM

#include "game/kernel/logger.hpp"
#include "game/kernel/engine.hpp"
#include "game/config.hpp"
#include "game/game/player.hpp"

#include "game/kernel/colors.hpp"

#include <raylib.h>

int main() {
    game::Engine engine;

    // Shut up raylib log.
    game::Logger::init(LOG_INFO, LOG_WARNING);

    auto config = game::defaultConfig;
    game::Logger::log(LOG_INFO, "Loading default config...");

    config.window.width = 800;
    config.window.height = 600;
    config.window.targetFPS = 120;
    config.window.showFPS = true;
    config.window.resizeable = true;

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

    game::Player player({
        static_cast<float>(config.window.width) / 2.0F - 16.0F,
        static_cast<float>(config.window.height) / 2.0F - 16.0F
    });

    while (engine.running()) {
        player.update(GetFrameTime());

        engine.drawFrame([&] {
            ClearBackground(game::colors::menuBackground);

            player.draw();

            if (config.window.showFPS) {
                engine.debugFPS();
            }
        });
    }

    engine.shutdown();
}
