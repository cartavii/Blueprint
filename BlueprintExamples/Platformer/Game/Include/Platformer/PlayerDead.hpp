#ifndef PLATFORMER_GAME_PLAYER_DEAD_HPP
#define PLATFORMER_GAME_PLAYER_DEAD_HPP

#include "Platformer/Player.hpp"

namespace Platformer {
class CastleLevel;

class PlayerDead final : public SpriteObject {
public:
    explicit PlayerDead(CastleLevel& castleLevel);

public:
    void update(float deltaTime);

private:
    CastleLevel&                          m_CastleLevel;
    Camera&                               m_Camera;
    sf::RectangleShape&                   m_Rectangle;
    Blueprint::Resources::TextureResource m_Resource;
    float                                 m_VerticalSpeed;
    const float                           m_Gravity;
    const float                           m_RotationSpeed;
    float                                 m_TimeElapsed;
    const float                           m_RestartTime;
};
} // Platformer

#endif // PLATFORMER_GAME_PLAYER_DEAD_HPP
