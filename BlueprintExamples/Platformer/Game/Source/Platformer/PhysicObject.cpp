#include "Platformer/PhysicObject.hpp"
#include "Blueprint/Core/Sign.hpp"

const float Platformer::PhysicObject::m_Gravity = 0.2f;

Platformer::PhysicObject::PhysicObject(const TilesHolder& ground, const TilesHolder& blocks, const sf::Vector2f& tileSize, const BoundingBox& boundingBox)
: SpriteObject(tileSize)
, m_Ground(ground)
, m_Blocks(blocks)
, m_Grounded(false)
, m_BoundingBox(boundingBox) {}

void Platformer::PhysicObject::addForce(const sf::Vector2f& force) {
    m_Velocity += force;
}

void Platformer::PhysicObject::addForceX(const float force) {
    m_Velocity.x += force;
}

void Platformer::PhysicObject::addForceY(float force) {
    m_Velocity.y += force;
}

void Platformer::PhysicObject::setVelocity(const sf::Vector2f& velocity) {
    m_Velocity = velocity;
}

void Platformer::PhysicObject::setVelocityX(const float velocity) {
    m_Velocity.x = velocity;
}

void Platformer::PhysicObject::setVelocityY(const float velocity) {
    m_Velocity.y = velocity;
}

sf::Vector2f Platformer::PhysicObject::getVelocity() const {
    return m_Velocity;
}

void Platformer::PhysicObject::setGrounded(bool grounded) {
    m_Grounded = grounded;
}

bool Platformer::PhysicObject::isGrounded() const {
    return m_Grounded;
}

void Platformer::PhysicObject::setBoundingBox(const BoundingBox& boundingBox) {
    m_BoundingBox = boundingBox;
}

const Platformer::BoundingBox& Platformer::PhysicObject::getBoundingBox() const {
    return m_BoundingBox;
}

sf::FloatRect Platformer::PhysicObject::getGlobalBounds() const {
    sf::FloatRect boundingBox(getPosition(), m_BoundingBox.size);
    boundingBox.position += m_BoundingBox.offset;
    boundingBox.position += m_Velocity;
    return boundingBox;
}

bool Platformer::PhysicObject::isCollidingSolid(const sf::Vector2f& velocity) {
    return isColliding(velocity, m_Ground) || isColliding(velocity, m_Blocks);
}

bool Platformer::PhysicObject::isColliding(const sf::Vector2f& velocity, const TilesHolder& tiles) {
    sf::FloatRect boundingBox(getPosition(), m_BoundingBox.size);
    boundingBox.position += m_BoundingBox.offset;
    boundingBox.position += velocity;
    for (const auto& [topLeft, bottomRight] : tiles) {
        if (const sf::FloatRect floatRect(topLeft, bottomRight - topLeft);
            floatRect.findIntersection(boundingBox)) {
            return true;
        }
    }
    return false;
}

void Platformer::PhysicObject::updateGravity(const float deltaTime) {
    m_Grounded = false;
    m_Velocity.y += m_Gravity * deltaTime;
    const float sign = Blueprint::Core::signF(m_Velocity.y);
    moveY(deltaTime);
    if (m_Velocity.y == 0.f && sign == 1.f) {
        m_Grounded = true;
    }
}

void Platformer::PhysicObject::moveX(const float deltaTime) {
    sf::RectangleShape& rectangle = getRectangle();
    float deltaHorizontalSpeed = m_Velocity.x * deltaTime;
    if (!isCollidingSolid(sf::Vector2f(deltaHorizontalSpeed, 0.f))) {
        rectangle.move(sf::Vector2f(deltaHorizontalSpeed, 0.f));
        return;
    }
    const float oldSign = Blueprint::Core::signF(deltaHorizontalSpeed);
    for (; isCollidingSolid(sf::Vector2f(deltaHorizontalSpeed, 0.f))
        && Blueprint::Core::signF(deltaHorizontalSpeed) == oldSign; deltaHorizontalSpeed -= oldSign) {}
    if (oldSign == Blueprint::Core::signF(deltaHorizontalSpeed)) {
        rectangle.move(sf::Vector2f(deltaHorizontalSpeed, 0.f));
    }
    m_Velocity.x = 0.f;
}

void Platformer::PhysicObject::moveY(const float deltaTime) {
    sf::RectangleShape& rectangle = getRectangle();
    float deltaVerticalSpeed = m_Velocity.y * deltaTime;
    if (!isCollidingSolid(sf::Vector2f(0.f, deltaVerticalSpeed))) {
        rectangle.move(sf::Vector2f(0.f, deltaVerticalSpeed));
        return;
    }
    const float oldSign = Blueprint::Core::signF(deltaVerticalSpeed);
    for (; isCollidingSolid(sf::Vector2f(0.f, deltaVerticalSpeed))
        && Blueprint::Core::signF(deltaVerticalSpeed) == oldSign; deltaVerticalSpeed -= oldSign) {}
    if (oldSign == Blueprint::Core::signF(deltaVerticalSpeed)) {
        rectangle.move(sf::Vector2f(0.f, deltaVerticalSpeed));
    }
    m_Velocity.y = 0.f;
}
