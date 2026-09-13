#pragma once

#include "game/game/entity.hpp"

namespace game {

    class Player final : public Entity {
    public:
        explicit Player(Vector2 position);

        void update(float deltaTime) override;
    };

} // namespace game
