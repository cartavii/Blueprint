#ifndef PLATFORMER_GAME_PHYSIC_OBJECT_HPP
#define PLATFORMER_GAME_PHYSIC_OBJECT_HPP

#include "Platformer/SpriteObject.hpp"
#include "Platformer/TilesHolder.hpp"

namespace Platformer {
struct BoundingBox {
    sf::Vector2f offset;
    sf::Vector2f size;
};

class PhysicObject : public SpriteObject {
public:
    explicit PhysicObject(const TilesHolder& ground, const TilesHolder& blocks, const sf::Vector2f& tileSize, const BoundingBox& boundingBox);

public:
    void addForce(const sf::Vector2f& force);
    void addForceX(float force);
    void addForceY(float force);
    void setVelocity(const sf::Vector2f& velocity);
    void setVelocityX(float velocity);
    void setVelocityY(float velocity);
    [[nodiscard]] sf::Vector2f getVelocity() const;

    void setGrounded(bool grounded);
    [[nodiscard]] bool isGrounded() const;

    void setBoundingBox(const BoundingBox& boundingBox);
    [[nodiscard]] const BoundingBox& getBoundingBox() const;
    [[nodiscard]] sf::FloatRect getGlobalBounds() const;

    [[nodiscard]] bool isCollidingSolid(const sf::Vector2f& velocity);
    [[nodiscard]] bool isColliding(const sf::Vector2f& velocity, const TilesHolder& tiles);

protected:
    void updateGravity(float deltaTime);

    void moveX(float deltaTime);
    void moveY(float deltaTime);

private:
    static const float m_Gravity;

    const TilesHolder& m_Ground;
    const TilesHolder& m_Blocks;

    sf::Vector2f m_Velocity;
    bool m_Grounded;

    BoundingBox m_BoundingBox;
};
} // Platformer

#endif // PLATFORMER_GAME_PHYSIC_OBJECT_HPP
