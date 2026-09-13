//
// Created by kwlew on 9/12/26.
//

#include "game/game/entity.hpp"

#include <algorithm>
#include <stdexcept>

namespace game {

namespace {

    constexpr EntityDefinition playerDefinition{
        .type = EntityType::Player,
        .name = "Player",
        .maximumHealth = 100.0f,
        .movementSpeed = 200.0f,
        .size = {32.0f, 32.0f},
        .color = {0, 100, 0, 255},
        .hostile = false
    };

}

    const EntityDefinition& getEntityDefinition(EntityType type) {
        switch (type) {
            case EntityType::Player:
                return playerDefinition;
        }

        throw std::invalid_argument("Unknown EntityType");
    }

    Entity::Entity(
        EntityType type,
        Vector2 position
    )
        : definition_(&getEntityDefinition(type)),
          position_(position),
          health_(definition_->maximumHealth) {}
            
    void Entity::update(float deltaTime) {
        position_.x += velocity_.x * deltaTime;
        position_.y += velocity_.y * deltaTime;
    }

    void Entity::draw() const {
        DrawRectangleV(
            position_,
            definition_->size,
            definition_->color
        );
    }

    EntityType Entity::type() const noexcept {
        return definition_->type;
    }

    std::string_view Entity::name() const noexcept {
        return definition_->name;
    }

    Vector2 Entity::position() const noexcept {
        return position_;
    }

    Vector2 Entity::velocity() const noexcept {
        return velocity_;
    }

    Vector2 Entity::size() const noexcept {
        return definition_->size;
    }

    float Entity::health() const noexcept {
        return health_;
    }

    float Entity::maximumHealth() const noexcept {
        return definition_->maximumHealth;
    }

    bool Entity::isAlive() const noexcept {
        return health_ > 0.0F;
    }

    bool Entity::isHostile() const noexcept {
        return definition_->hostile;
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
