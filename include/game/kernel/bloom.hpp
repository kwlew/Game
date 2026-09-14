#pragma once

#include <raylib.h>

namespace game {

    // Screen-space bloom post-process effect.
    //
    // "Bloom" is the soft halo you see around very bright light in a photo
    // or through the human eye - it happens because intense light scatters
    // past the edges of whatever emitted it. Games fake this with a
    // shader, in two steps:
    //   1. Render the whole scene into an off-screen texture instead of
    //      straight to the screen (`capture`).
    //   2. Run a fragment shader over that texture which finds the pixels
    //      brighter than a threshold, blurs a copy of just those pixels,
    //      and adds the blurred copy back on top of the original image
    //      (`draw`). See the shader source in bloom.cpp for how.
    //
    // It runs once per frame on the whole rendered image rather than once
    // per object, so any bright color already glows for free - nothing
    // object-specific to opt in. Typical use cases: glowing player/enemy
    // auras, pickups & power-ups, magic spells, explosions, lava/fire,
    // laser bolts, neon signs - anything drawn with a bright, saturated
    // color that should visually pop against a darker scene.
    //
    // Usage:
    //   game::Bloom bloom(GetScreenWidth(), GetScreenHeight());
    //   ...
    //   bloom.capture([&] {
    //       ClearBackground(...);
    //       // ... normal scene drawing goes here ...
    //   });
    //   bloom.draw(); // composites the bloom-shaded scene onto the screen
    class Bloom final {
    public:
        Bloom(int width, int height);
        ~Bloom() noexcept;

        Bloom(const Bloom&) = delete;
        Bloom& operator=(const Bloom&) = delete;
        Bloom(Bloom&&) = delete;
        Bloom& operator=(Bloom&&) = delete;

        // Recreates the off-screen render target at a new size, e.g. after
        // the window is resized.
        void resize(int width, int height);

        // Redirects rendering into the off-screen target for the duration
        // of `draw`. Call this once per frame wrapping all of your normal
        // scene-drawing code.
        template <typename DrawFn>
        void capture(DrawFn&& draw) const {
            BeginTextureMode(target_);
            draw();
            EndTextureMode();
        }

        // Draws the captured scene onto the currently active render
        // target (normally the screen) through the bloom shader.
        void draw() const;

    private:
        void load(int width, int height);
        void unload() noexcept;

        RenderTexture2D target_{};
        Shader shader_{};
        int resolutionLoc_ = -1;
    };

} // namespace game
