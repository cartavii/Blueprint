#include "Platformer/Hedgehog.hpp"
#include "Platformer/Player.hpp"
#include "Platformer/CastleLevelExt.hpp"
#include "Platformer/Loader.hpp"

Platformer::Hedgehog::Hedgehog(CastleLevelExt& castleLevel)
: PhysicObject(castleLevel.getGround(), castleLevel.getBlocks(), sf::Vector2f(16.f, 16.f), {{3 - 8, 9}, {10, 7}})
, m_Player(castleLevel.getPlayer())
, m_CastleLevel(castleLevel)
, m_FrameDuration(5.f)
, m_Elapsed(0.f)
, m_Frame(0)
, m_HorizontalSpeed(0.4f)
, m_Direction(-1.f) {
    getRectangle().setOrigin(sf::Vector2f(8.f, 0.f));
}

void Platformer::Hedgehog::load(const nlohmann::ordered_json& data) {
    PhysicObject::load(data);
    if (data.contains("Position")) {
        setPosition(Loader::loadVector2f(data, "Position") + getRectangle().getOrigin());
    }
}

void Platformer::Hedgehog::update(const float deltaTime) {
    updateGravity(deltaTime);
    setVelocityX(m_HorizontalSpeed * m_Direction);
    moveX(deltaTime);
    m_Elapsed += deltaTime;
    if (getVelocity().x == 0.f) {
        m_Direction *= -1.f;
        getRectangle().setScale(sf::Vector2f(-m_Direction, 1.f));
    }
    if (!m_CastleLevel.isPlayerDead() && getGlobalBounds().findIntersection(m_Player.getGlobalBounds())) {
        m_CastleLevel.setPlayerDead();
    }
    while (m_Elapsed > m_FrameDuration) {
        m_Elapsed -= m_FrameDuration;
        m_Frame++;
    }
    setTileIndex(sf::Vector2i(m_Frame % 4, 0));
}

void Platformer::Hedgehog::render(sf::RenderTarget& renderTarget) {
    SpriteObject::render(renderTarget);
}
