#ifndef PLATFORMER_GAME_FIRST_LEVEL_HPP
#define PLATFORMER_GAME_FIRST_LEVEL_HPP

#include "Platformer/CastleLevel.hpp"
#include "Platformer/FloatingHint.hpp"

namespace Platformer {
class FirstLevel final : public CastleLevel {
public:
    explicit FirstLevel(Blueprint::Game::SceneManager& manager);

private:
    void load(const nlohmann::ordered_json& data) override;

    void update(const sf::Time& deltaTime) override;

    void render(sf::RenderTarget& renderTarget) override;

private:
    const float m_HintDuration;
    const float m_HintDistance;
    const float m_HintSpace;
    FloatingHint m_JumpHint;
    FloatingHint m_LeftHint;
    FloatingHint m_RightHint;
    FloatingHint m_DownHint;
};
} // Platformer

#endif // PLATFORMER_GAME_FIRST_LEVEL_HPP
