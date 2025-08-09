#ifndef PLATFORMER_EDITOR_LAST_LEVEL_HPP
#define PLATFORMER_EDITOR_LAST_LEVEL_HPP

#include "Platformer/CastleLevel.hpp"

namespace Platformer {
class LastLevel final : public CastleLevel {
public:
    LastLevel() = default;

private:
    void load(const nlohmann::ordered_json& data) override;

    void loadPalette();

    void loadRandos(const nlohmann::ordered_json& data);

    void save(nlohmann::ordered_json& data) override;

    void update() override;

    void updateRandoAdd();

    void updateRandoRemove();

    void render(sf::RenderTarget& renderTarget) override;

private:
    SpriteObjectsHolder m_RandoHolder;
};
} // Platformer

#endif // PLATFORMER_EDITOR_LAST_LEVEL_HPP
