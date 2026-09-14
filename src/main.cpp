// File created by kwlew on 2026-12-09 @ 2:18 AM

#include "game/kernel/logger.hpp"
#include "game/kernel/engine.hpp"
#include "game/config.hpp"
#include "game/game/player.hpp"
#include "game/game/enemy.hpp"

#include "game/kernel/colors.hpp"
#include "game/kernel/bloom.hpp"

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

    game::Enemy enemy({
        static_cast<float>(config.window.width) / 4.0F - 16.0F,
        static_cast<float>(config.window.height) / 4.0F - 16.0F
    });

    // Post-process bloom: makes bright/saturated colors (like the
    // player's) glow. Needs a window/GL context, so it's created after
    // engine.initialize() and sized to match it.
    game::Bloom bloom(config.window.width, config.window.height);

    while (engine.running()) {
        if (config.window.resizeable && IsWindowResized()) {
            bloom.resize(GetScreenWidth(), GetScreenHeight());
        }

        player.update(GetFrameTime());
        enemy.update(GetFrameTime(), player.position());

        engine.drawFrame([&] {
            // Draw the scene into bloom's off-screen target instead of
            // straight to the screen, then composite it through the
            // shader so bright entities (the player) glow.
            bloom.capture([&] {
                ClearBackground(game::colors::menuBackground);

                player.draw();
                enemy.draw();
            });
            bloom.draw();

            // Drawn after bloom, straight to screen, so UI text stays
            // crisp instead of also being blurred/glowing.
            if (config.window.showFPS) {
                engine.debugFPS();
            }
        });
    }

    engine.shutdown();
}
