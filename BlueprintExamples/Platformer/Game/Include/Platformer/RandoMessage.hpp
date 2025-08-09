#ifndef PLATFORMER_GAME_RANDO_MESSAGE_HPP
#define PLATFORMER_GAME_RANDO_MESSAGE_HPP

#include "Platformer/SpriteObject.hpp"

namespace Platformer {
class CastleLevel;
class RandoMessage final : public SpriteObject {
public:
    explicit RandoMessage(CastleLevel& castleLevel);

public:
    void load(const nlohmann::ordered_json& data) override;

    void initialize(const sf::Vector2f& startingPosition);

    void update(float deltaTime);

    [[nodiscard]] bool isElapsed() const;

private:
    CastleLevel& m_CastleLevel;
    const float m_FadeInDuration;
    const float m_StayDuration;
    const float m_FadeOutDuration;
    const float m_VerticalSpeed;
    float m_Elapsed;
    Blueprint::Resources::TextureResource m_Resource[4];
};
} // Platformer

#endif // PLATFORMER_GAME_RANDO_MESSAGE_HPP
