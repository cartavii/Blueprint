#include "Platformer/FloatingHint.hpp"
#include "Platformer/Random.hpp"
#include <cmath>

Platformer::FloatingHint::FloatingHint(const sf::Vector2f& tileSize, const float duration, const float distance)
: SpriteObject(tileSize)
, m_Duration(duration)
, m_Distance(distance)
, m_Elapsed(Random::randomRange(0.f, duration)) {}

void Platformer::FloatingHint::update(const float deltaTime) {
    m_Elapsed += deltaTime;
    const float progress = std::sin(m_Elapsed / m_Duration);
    const float currentDistance = m_Distance * progress;
    SpriteObject::setPosition(m_Position + sf::Vector2f(0.f, currentDistance));
}

void Platformer::FloatingHint::setPosition(const sf::Vector2f& position) {
    m_Position = position;
}

const sf::Vector2f& Platformer::FloatingHint::getPosition() const {
    return m_Position;
}

void Platformer::FloatingHint::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_Resource = textureResource;
    SpriteObject::setTextureResource(textureResource);
}
