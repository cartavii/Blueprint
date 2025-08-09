#ifndef PLATFORMER_GAME_RANDO_HPP
#define PLATFORMER_GAME_RANDO_HPP

#include "Platformer/RandoMessage.hpp"
#include "Platformer/PhysicObject.hpp"

namespace Platformer {
class CastleLevel;
class Rando final : public PhysicObject {
public:
    explicit Rando(CastleLevel& castleLevel);

public:
    void load(const nlohmann::ordered_json& data) override;

    void update(float deltaTime);

    [[nodiscard]] RandoMessage& getMessage();

private:
    const float m_JumpForceMin;
    const float m_JumpForceMax;
    const float m_JumpWaitDurationMin;
    const float m_JumpWaitDurationMax;
    const float m_MessageSpawnDurationMin;
    const float m_MessageSpawnDurationMax;
    float m_JumpWaitDuration;
    float m_JumpWaitElapsed;
    float m_MessageSpawnDuration;
    float m_MessageSpawnElapsed;
    RandoMessage m_RandoMessage;
};
} // Platformer

#endif // PLATFORMER_GAME_RANDO_HPP
