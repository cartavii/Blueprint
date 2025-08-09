#include "Platformer/Rando.hpp"
#include "Platformer/CastleLevel.hpp"
#include "Platformer/Loader.hpp"
#include "Platformer/Random.hpp"

Platformer::Rando::Rando(CastleLevel& castleLevel)
: PhysicObject(castleLevel.getGround(), castleLevel.getBlocks(), sf::Vector2f(16.f, 16.f), {{4, 3}, {10, 13}})
, m_JumpForceMin(2.f)
, m_JumpForceMax(3.f)
, m_JumpWaitDurationMin(2.f)
, m_JumpWaitDurationMax(6.f)
, m_MessageSpawnDurationMin(80.f)
, m_MessageSpawnDurationMax(120.f)
, m_JumpWaitDuration(Random::randomRange(m_JumpWaitDurationMin, m_JumpWaitDurationMax))
, m_JumpWaitElapsed(0.f)
, m_MessageSpawnDuration(Random::randomRange(m_MessageSpawnDurationMin, m_MessageSpawnDurationMax))
, m_MessageSpawnElapsed(m_MessageSpawnDuration)
, m_RandoMessage(castleLevel) {}

void Platformer::Rando::load(const nlohmann::ordered_json& data) {
    PhysicObject::load(data);
    if (data.contains("Position")) {
        setPosition(Loader::loadVector2f(data, "Position"));
    }
    m_RandoMessage.load(data);
}

void Platformer::Rando::update(const float deltaTime) {
    updateGravity(deltaTime);
    if (isGrounded()) {
        if (m_JumpWaitElapsed >= m_JumpWaitDuration) {
            setVelocityY(-Random::randomRange(m_JumpForceMin, m_JumpForceMax));
            m_JumpWaitElapsed = 0.f;
            m_JumpWaitDuration = Random::randomRange(m_JumpWaitDurationMin, m_JumpWaitDurationMax);
        }
        m_JumpWaitElapsed += deltaTime;
    }
    if (m_RandoMessage.isElapsed()) {
        m_MessageSpawnElapsed += deltaTime;
        if (m_MessageSpawnElapsed >= m_MessageSpawnDuration) {
            m_RandoMessage.initialize(getPosition() - sf::Vector2f(0.f, 16.f));
            m_MessageSpawnDuration = 0.f;
            m_MessageSpawnDuration = Random::randomRange(m_MessageSpawnDurationMin, m_MessageSpawnDurationMax);
        }
    } else {
        m_RandoMessage.update(deltaTime);
    }
}

Platformer::RandoMessage& Platformer::Rando::getMessage() {
    return m_RandoMessage;
}
