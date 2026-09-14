#include "game/kernel/bloom.hpp"

namespace game {

    namespace {

        // A single-pass approximation of bloom. "Real" engines usually run
        // 3 separate shader passes - threshold, blur, combine - each
        // reading the pass before it. This folds all three into one pass
        // (redoing the threshold+blur per pixel) so there's only one
        // shader and one render texture to manage, at the cost of being a
        // little heavier on the GPU. Plenty fast for a small 2D game.
        constexpr const char* kFragmentShaderSource = R"glsl(
            #version 330

            in vec2 fragTexCoord;
            in vec4 fragColor;

            uniform sampler2D texture0;
            uniform vec2 resolution;

            out vec4 finalColor;

            // Step 1: threshold. Only pixels at or above this brightness
            // (0-1 luminance) count as a light source and get blurred into
            // a glow. Raise it so only the strongest highlights bloom,
            // lower it to make more of the scene glow.
            const float threshold = 0.6;

            // Step 2: blur. Kernel radius/spread in pixels - bigger means
            // a softer, wider glow but more texture samples (more GPU
            // cost, since the kernel is squared: (2*radius+1)^2 samples).
            const int kernelRadius = 4;
            const float spread = 1.5;

            void main()
            {
                vec4 baseColor = texture(texture0, fragTexCoord);

                vec2 texelSize = spread / resolution;
                vec3 bloomSum = vec3(0.0);
                float sampleCount = 0.0;

                // Box-blur a bright-pass of the neighborhood around this
                // pixel: samples below `threshold` contribute nothing, so
                // dark areas stay dark instead of smearing glow into each
                // other.
                for (int x = -kernelRadius; x <= kernelRadius; x++)
                {
                    for (int y = -kernelRadius; y <= kernelRadius; y++)
                    {
                        vec3 sampleColor = texture(texture0, fragTexCoord + vec2(x, y) * texelSize).rgb;

                        // Perceptual brightness (green reads brighter to
                        // the eye than red/blue, hence the uneven weights).
                        float luminance = dot(sampleColor, vec3(0.2126, 0.7152, 0.0722));
                        float contribution = max(luminance - threshold, 0.0);

                        bloomSum += sampleColor * contribution;
                        sampleCount += 1.0;
                    }
                }

                vec3 bloom = bloomSum / sampleCount;

                // Step 3: combine. Add the glow on top of the untouched
                // original image so edges/detail stay sharp - only the
                // glow itself is blurred, not the whole scene.
                finalColor = vec4(baseColor.rgb + bloom, baseColor.a) * fragColor;
            }
        )glsl";

    } // namespace

    Bloom::Bloom(int width, int height) {
        load(width, height);
    }

    Bloom::~Bloom() noexcept {
        unload();
    }

    void Bloom::load(int width, int height) {
        target_ = LoadRenderTexture(width, height);
        shader_ = LoadShaderFromMemory(nullptr, kFragmentShaderSource);
        resolutionLoc_ = GetShaderLocation(shader_, "resolution");

        const float resolution[2] = {
            static_cast<float>(width),
            static_cast<float>(height)
        };
        SetShaderValue(shader_, resolutionLoc_, resolution, SHADER_UNIFORM_VEC2);
    }

    void Bloom::unload() noexcept {
        UnloadShader(shader_);
        UnloadRenderTexture(target_);
    }

    void Bloom::resize(int width, int height) {
        unload();
        load(width, height);
    }

    void Bloom::draw() const {
        BeginShaderMode(shader_);

        // Render textures are stored bottom-up on the GPU, so the source
        // rectangle's height is negated to flip the image right-side up.
        DrawTextureRec(
            target_.texture,
            {
                0.0F,
                0.0F,
                static_cast<float>(target_.texture.width),
                -static_cast<float>(target_.texture.height)
            },
            {0.0F, 0.0F},
            WHITE
        );

        EndShaderMode();
    }

} // namespace game
