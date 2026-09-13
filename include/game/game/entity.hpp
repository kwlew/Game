#pragma once

#include <raylib.h>

#include <string_view>

namespace game {

    enum class EntityType {
        Player,
    };

    struct EntityDefinition {
        EntityType type;
        std::string_view name;

        float maximumHealth;
        float movementSpeed;

        Vector2 size;
        Color color;

        bool hostile;
    };

    [[nodiscard]] const EntityDefinition& getEntityDefinition(EntityType type);

    class Entity {
    public:
        Entity(EntityType type, Vector2 position);

        virtual ~Entity() = default;

        virtual void update(float deltaTime);
        virtual void draw() const;

        [[nodiscard]] EntityType type() const noexcept;
        [[nodiscard]] std::string_view name() const noexcept;
        [[nodiscard]] Vector2 position() const noexcept;
        [[nodiscard]] Vector2 velocity() const noexcept;
        [[nodiscard]] Vector2 size() const noexcept;
        [[nodiscard]] float health() const noexcept;
        [[nodiscard]] float maximumHealth() const noexcept;
        [[nodiscard]] bool isAlive() const noexcept;
        [[nodiscard]] bool isHostile() const noexcept;

        void setPosition(Vector2 position) noexcept;
        void damage(float amount) noexcept;
        void heal(float amount) noexcept;

    protected:
        const EntityDefinition* definition_;

        Vector2 position_{};
        Vector2 velocity_{};

        float health_{};
    };

} // namespace game
