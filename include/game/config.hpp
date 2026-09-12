#pragma once

namespace game {

    struct WindowSettings final {
        int width;
        int height;
        int targetFPS;
        bool showFPS;
    };

    struct GameConfig final {
        WindowSettings window;
    };

    inline constexpr GameConfig defaultConfig{
        .window = {
            .width = 800,
            .height = 600,
            .targetFPS = 60,
            .showFPS = true
        }
    };
}