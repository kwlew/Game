#pragma once

#include "game/game/entity.hpp"

namespace game {

    class Enemy final : public Entity {
    public:
        explicit Enemy(Vector2 position);

        void update(float deltaTime) override;
        void update(float deltaTime, Vector2 targetPosition);

    private:
        // Enemy-only stat
        static constexpr float kAttackPower = 10.0F;

        // Last known position to chase, in case update(float) is called polymorphically
        Vector2 target_{};
    };

} // namespace game