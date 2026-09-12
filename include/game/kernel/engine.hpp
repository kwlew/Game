// File created by kwlew on 2026-12-09 @ 3:00 AM
#pragma once

#include "window.hpp"
#include "game/config.hpp"

#include <functional>
#include <optional>

namespace game {

    class Engine {
    public:
        bool initialize(int width, int height, const char* title, int targetFPS);
        bool initialize(const WindowSettings& settings, const char* title);
        void shutdown() noexcept;
        [[nodiscard]] bool running() const noexcept;
        void drawFrame(const std::function<void()>& draw);
        void debugFPS() const noexcept;
        void setFPS(int fps);
        void setResolution(int width, int height) const noexcept;
        void setWindowName(const char* title) const noexcept;

    private:
        std::optional<Window> window_;
    };

}
