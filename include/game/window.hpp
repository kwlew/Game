#pragma once

#include <vector>

namespace game {
    class Window final {
    public:
        Window(int width, int height, const char* title);
        ~Window() noexcept;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        void setTargetFPS(int fps) noexcept;
        void setResolution(int width, int height) const noexcept;
        void setWindowName(const char* title) const noexcept;
        [[nodiscard]] int getFPS() const noexcept;
        [[nodiscard]] int getWidth() const noexcept;
        [[nodiscard]] int getHeight() const noexcept;
        [[nodiscard]] std::vector<int> getBoth() const noexcept;
        [[nodiscard]] bool shouldClose() const noexcept;
    };
}