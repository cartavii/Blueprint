#ifndef PLATFORMER_GAME_PLAYER_HPP
#define PLATFORMER_GAME_PLAYER_HPP

#include "Platformer/TilesHolder.hpp"
#include "Platformer/PhysicObject.hpp"

namespace Platformer {
class CastleLevel;
class Camera;

class Player final : public PhysicObject {
public:
    explicit Player(CastleLevel& castleLevel);

public:
    void load(const nlohmann::ordered_json& data) override;

    void update(float deltaTime);

private:
    void loadTextures();

    void updateWalking(float deltaTime);
    void updateJump(float deltaTime);
    void updateCamera();
    void updateDoor();
    void updateTexture(float deltaTime);

private:
    CastleLevel& m_CastleLevel;
    Camera& m_Camera;
    Blueprint::Resources::TextureResource m_IdleResource;
    Blueprint::Resources::TextureResource m_WalkResource;
    Blueprint::Resources::TextureResource m_JumpResource;
    const sf::Vector2f m_Origin;
    const float m_HorizontalSpeed;
    const float m_JumpForce;
    float m_WalkFrame;
    float m_WalkTime;
    const float m_WalkSwitchTime;
};
} // Platformer

#endif // PLATFORMER_GAME_PLAYER_HPP
