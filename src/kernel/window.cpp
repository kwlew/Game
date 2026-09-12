// File created by kwlew on 2026-12-09 @ 2:30 AM

#include "../../include/game/kernel/window.hpp"

#include <raylib.h>

#include <stdexcept>

namespace game {
    Window::Window(int width, int height, const char* title) {
        if (::IsWindowReady()) {
            throw std::runtime_error("Window is already initialized.");
        }

        ::InitWindow(width, height, title);

        if (!::IsWindowReady()) {
            throw std::runtime_error("Failed to initialize window.");
        }
    }

    Window::~Window() noexcept {
        CloseWindow();
    }

    void Window::setTargetFPS(int fps) noexcept {
        SetTargetFPS(fps);
    }

    void Window::setResolution(int width, int height) const noexcept {
        if (::IsWindowReady()) {
            SetWindowSize(width, height);
        }
    }

    void Window::setWindowName(const char* title) const noexcept {
        if (::IsWindowReady()) {
            SetWindowTitle(title);
        }
    }

    [[nodiscard]] int Window::getFPS() const noexcept {
        return GetFPS();
    }

    [[nodiscard]] int Window::getWidth() const noexcept {
        return GetScreenWidth();
    }

    [[nodiscard]] int Window::getHeight() const noexcept {
        return GetScreenHeight();
    }

    [[nodiscard]] std::vector<int> Window::getBoth() const noexcept {
        return {GetScreenWidth(), GetScreenHeight()};
    }

    [[nodiscard]] bool Window::shouldClose() const noexcept {
        return WindowShouldClose();
    }
}