#ifndef PLATFORMER_GAME_LAST_SCENE_HPP
#define PLATFORMER_GAME_LAST_SCENE_HPP

#include "Platformer/CastleLevel.hpp"
#include "Platformer/RandosHolder.hpp"

namespace Platformer {
class LastLevel final : public CastleLevel {
public:
    explicit LastLevel(Blueprint::Game::SceneManager& manager);

private:
    void load(const nlohmann::ordered_json& data) override;

    void update(const sf::Time& deltaTime) override;

    void render(sf::RenderTarget& renderTarget) override;

private:
    RandosHolder m_Randos;
};
} // Platformer

#endif // PLATFORMER_GAME_LAST_SCENE_HPP
