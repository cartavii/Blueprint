#ifndef PLATFORMER_CASTLE_LEVEL_EXT_HPP
#define PLATFORMER_CASTLE_LEVEL_EXT_HPP

#include "Platformer/CastleLevel.hpp"
#include "Platformer/HedgehogsHolder.hpp"

namespace Platformer {
class CastleLevelExt final : public CastleLevel {
public:
    explicit CastleLevelExt(Blueprint::Game::SceneManager& manager);

private:
    void load(const nlohmann::ordered_json& data) override;

    void update(const sf::Time& deltaTime) override;

    void render(sf::RenderTarget& renderTarget) override;

private:
    HedgehogsHolder m_HedgehogsHolder;
};
} // Platformer

#endif // PLATFORMER_CASTLE_LEVEL_EXT_HPP
