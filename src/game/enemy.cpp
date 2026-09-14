#include "game/game/enemy.hpp"
#include "game/game/player.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>

namespace game {

    namespace {
        constexpr EntityDefinition EnemyDefinition{
            .name = "Enemy",
            .maximumHealth = 50.0f,
            .movementSpeed = 150.0f,
            .size = {32.0f, 32.0f},
            .color = {100, 0, 0, 255},
            .hostile = true
        };
    }

    Enemy::Enemy(Vector2 position)
        : Entity(EnemyDefinition, position), target_(position) {}

    void Enemy::update(float deltaTime) {
        // Fallback for callers using the base Entity interface: chase the
        // last known target position instead of the player directly.
        update(deltaTime, target_);
    }

    void Enemy::update(float deltaTime, Vector2 targetPosition) {
        target_ = targetPosition;

        // Simple AI: Move towards the given target (e.g. the player)
        Vector2 direction = {
            targetPosition.x - position_.x,
            targetPosition.y - position_.y
        };

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
    }
}