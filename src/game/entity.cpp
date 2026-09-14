//
// Created by kwlew on 9/12/26.
//

#include "game/game/entity.hpp"

#include <algorithm>

namespace game {

    Entity::Entity(
        const EntityDefinition& definition,
        Vector2 position
    )
        : definition_(definition),
          position_(position),
          health_(definition_.maximumHealth) {}

    void Entity::update(float deltaTime) {
        position_.x += velocity_.x * deltaTime;
        position_.y += velocity_.y * deltaTime;
    }

    void Entity::draw() const {
        DrawRectangleV(
            position_,
            definition_.size,
            definition_.color
        );
    }

    std::string_view Entity::name() const noexcept {
        return definition_.name;
    }

    Vector2 Entity::position() const noexcept {
        return position_;
    }

    Vector2 Entity::velocity() const noexcept {
        return velocity_;
    }

    Vector2 Entity::size() const noexcept {
        return definition_.size;
    }

    float Entity::health() const noexcept {
        return health_;
    }

    float Entity::maximumHealth() const noexcept {
        return definition_.maximumHealth;
    }

    bool Entity::isAlive() const noexcept {
        return health_ > 0.0F;
    }

    bool Entity::isHostile() const noexcept {
        return definition_.hostile;
    }

    float Entity::getX() const noexcept {
        return position_.x;
    }

    float Entity::getY() const noexcept {
        return position_.y;
    }

    void Entity::setPosition(Vector2 position) noexcept {
        position_ = position;
    }

    void Entity::damage(float amount) noexcept {
        if (amount <= 0.0F || !isAlive()) {
            return;
        }

        health_ = std::max(0.0F, health_ - amount);
    }

    void Entity::heal(float amount) noexcept {
        if (amount <= 0.0F || !isAlive()) {
            return;
        }

        health_ = std::min(maximumHealth(), health_ + amount);
    }

} // namespace game
