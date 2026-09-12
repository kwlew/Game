// File created by kwlew on 2026-12-09 @ 3:00 AM

#include "game/engine.hpp"
#include "game/logger.hpp"

#include <exception>

namespace game {
    bool Engine::initialize(int width, int height, const char* title, int targetFPS) {
        if (window_) {
            Logger::log(LOG_WARNING, "Engine is already initialized.");
            return false;
        }

        try {
            window_.emplace(width, height, title);
            window_->setTargetFPS(targetFPS);
            Logger::log(
                LOG_INFO,
                "Engine initialized (%dx%d, %d FPS)",
                width,
                height,
                targetFPS
            );
            return true;
        } catch (const std::exception& exception) {
            Logger::log(LOG_ERROR, "Failed to initialize engine: %s", exception.what());
            return false;
        }
    }

    bool Engine::initialize(const WindowSettings& settings, const char* title) {
        return initialize(settings.width, settings.height, title, settings.targetFPS);
    }

    void Engine::shutdown() noexcept {
        if (window_) {
            window_.reset();
            Logger::log(LOG_INFO, "Engine shut down cleanly");
        }
    }

    [[nodiscard]] bool Engine::running() const noexcept {
        return window_.has_value() && !window_->shouldClose();
    }

    void Engine::drawFrame(const std::function<void()>& draw) {
        if (!window_) {
            return;
        }

        BeginDrawing();

        try {
            draw();
        } catch (...) {
            EndDrawing();
            throw; // Rethrow the exception after cleaning up
        }

        EndDrawing();
    }

    void Engine::debugFPS() const noexcept {
        if (window_.has_value()) {
            DrawFPS(10, 10);
        }
    }

    void Engine::setFPS(int fps) {
        if (window_.has_value()) {
            window_->setTargetFPS(fps);
        }
    }

    void Engine::setResolution(int width, int height) const noexcept {
        if (window_.has_value()) {
            window_->setResolution(width, height);
        }
    }

    void Engine::setWindowName(const char* title) const noexcept {
        if (window_.has_value()) {
            window_->setWindowName(title);
        }
    }

}
