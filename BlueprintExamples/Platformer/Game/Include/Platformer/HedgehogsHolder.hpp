#ifndef PLATFORMER_GAME_HEDGEHOGS_HOLDER_HPP
#define PLATFORMER_GAME_HEDGEHOGS_HOLDER_HPP

#include "Platformer/Hedgehog.hpp"

#include <vector>

namespace Platformer {
class HedgehogsHolder {
public:
    explicit HedgehogsHolder(CastleLevelExt& castleLevel);

public:
    void load(const nlohmann::ordered_json& data);

    void loadResources();

    void loadHedgehogs(const nlohmann::ordered_json& data);

    void loadHintHogs(const nlohmann::ordered_json& data);

    void update(float deltaTime);

    void render(sf::RenderTarget& renderTarget);

private:
    CastleLevelExt& m_CastleLevel;
    Blueprint::Resources::TextureResource m_Resource;
    Blueprint::Resources::TextureResource m_HintResource;
    std::vector<Hedgehog*> m_Hedgehogs;
};
} // Platformer

#endif // PLATFORMER_GAME_HEDGEHOGS_HOLDER_HPP
