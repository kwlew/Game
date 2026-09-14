#include "game/game/player.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>

namespace game {

namespace {

    // Player's own definition
    constexpr EntityDefinition PlayerDefinition{
        .name = "Player",
        .maximumHealth = 100.0f,
        .movementSpeed = 200.0f,
        .size = {32.0f, 32.0f},
        // Bright/saturated so it crosses the bloom shader's brightness
        // threshold and actually glows (see game::Bloom).
        .color = {80, 250, 160, 255},
        .hostile = false
    };

}

    Player::Player(Vector2 position)
        : Entity(PlayerDefinition, position) {}

    void Player::update(float deltaTime) {
        Vector2 direction{};

        // Handle input
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            direction.x -= 1.0F;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            direction.x += 1.0F;
        }
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            direction.y -= 1.0F;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            direction.y += 1.0F;
        }

        const float lengthSquared =
            direction.x * direction.x + direction.y * direction.y;

        if (lengthSquared > 0.0F) {
            const float inverseLength = 1.0F / std::sqrt(lengthSquared);
            direction.x *= inverseLength;
            direction.y *= inverseLength;
        }

        velocity_.x = direction.x * definition_.movementSpeed;
        velocity_.y = direction.y * definition_.movementSpeed;

        Entity::update(deltaTime);

        const float maximumX = std::max(
            0.0F,
            static_cast<float>(GetScreenWidth()) - definition_.size.x
        );
        const float maximumY = std::max(
            0.0F,
            static_cast<float>(GetScreenHeight()) - definition_.size.y
        );

        position_.x = std::clamp(position_.x, 0.0F, maximumX);
        position_.y = std::clamp(position_.y, 0.0F, maximumY);
    }

    float Player::stamina() const noexcept {
        return stamina_;
    }

    float Player::maximumStamina() const noexcept {
        return kMaximumStamina;
    }

} // namespace game
