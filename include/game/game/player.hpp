#pragma once

#include "game/game/entity.hpp"

namespace game {

    class Player final : public Entity {
    public:
        explicit Player(Vector2 position);

        void update(float deltaTime) override;

        [[nodiscard]] float stamina() const noexcept;
        [[nodiscard]] float maximumStamina() const noexcept;

    private:
        // Player-only stat
        static constexpr float kMaximumStamina = 100.0F;

        float stamina_ = kMaximumStamina;
    };

} // namespace game
