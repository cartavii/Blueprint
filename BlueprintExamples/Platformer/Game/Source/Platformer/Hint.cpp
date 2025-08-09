#include "Platformer/Hint.hpp"


Platformer::Hint::Hint()
: SpriteObject(sf::Vector2f(32.f, 32.f))
, m_FrameDuration(4.f)
, m_Elapsed(0.f)
, m_Offset(sf::Vector2f(-20.f, -28.f)) {}

void Platformer::Hint::update(const float deltaTime) {
    m_Elapsed += deltaTime;
    while (m_Elapsed > m_FrameDuration) {
        m_Frame++;
        m_Elapsed -= m_FrameDuration;
    }
    setTileIndex(sf::Vector2i(m_Frame % 3, 0));
}

void Platformer::Hint::setPosition(const sf::Vector2f& position) {
    SpriteObject::setPosition(position + m_Offset);
}
