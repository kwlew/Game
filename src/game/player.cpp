#include "game/game/player.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>

namespace game {

    Player::Player(Vector2 position)
        : Entity(EntityType::Player, position) {}

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

        velocity_.x = direction.x * definition_->movementSpeed;
        velocity_.y = direction.y * definition_->movementSpeed;

        Entity::update(deltaTime);

        const float maximumX = std::max(
            0.0F,
            static_cast<float>(GetScreenWidth()) - definition_->size.x
        );
        const float maximumY = std::max(
            0.0F,
            static_cast<float>(GetScreenHeight()) - definition_->size.y
        );

        position_.x = std::clamp(position_.x, 0.0F, maximumX);
        position_.y = std::clamp(position_.y, 0.0F, maximumY);
    }

} // namespace game
