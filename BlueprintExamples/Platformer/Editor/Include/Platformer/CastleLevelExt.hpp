#ifndef PLATFORMER_EDITOR_CASTLE_LEVEL_EXT_HPP
#define PLATFORMER_EDITOR_CASTLE_LEVEL_EXT_HPP

#include "Platformer/CastleLevel.hpp"
#include "Platformer/SpriteObjectsHolder.hpp"

namespace Platformer {
class CastleLevelExt final : public CastleLevel {
private:
    void load(const nlohmann::ordered_json& data) override;

    void loadPalette();

    void loadHedgehogs(const nlohmann::ordered_json& data);

    void loadHintHogs(const nlohmann::ordered_json& data);

    void save(nlohmann::ordered_json& data) override;

    void update() override;

    void updateHedgehogsAdd();

    void updateHedgehogsRemove();

    void updateHintHogsAdd();

    void updateHintHogsRemove();

    void render(sf::RenderTarget& renderTarget) override;

private:
    SpriteObjectsHolder m_Hedgehogs;
    SpriteObjectsHolder m_HintHogs;
};
} // Platformer

#endif // PLATFORMER_EDITOR_CASTLE_LEVEL_EXT_HPP
