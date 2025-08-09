#ifndef PLATFORMER_EDITOR_FIRST_LEVEL_HPP
#define PLATFORMER_EDITOR_FIRST_LEVEL_HPP

#include "Platformer/CastleLevel.hpp"

namespace Platformer {
class FirstLevel final : public CastleLevel {
public:
    FirstLevel();

private:
    void load(const nlohmann::ordered_json& data) override;

    void loadPalette();

    void loadMovementKeys(const nlohmann::ordered_json& data);

    void loadOpenKey(const nlohmann::ordered_json& data);

    void save(nlohmann::ordered_json& data) override;

    void saveMovementKeys(nlohmann::ordered_json& data);

    void saveOpenKey(nlohmann::ordered_json& data);

    void update() override;

    void updateMovementPosition();

    void setMovementPosition(sf::Vector2f topLeft);

    void updateOpenPosition();

    void render(sf::RenderTarget& renderTarget) override;

private:
    const float m_KeySpace;
    SpriteObject m_JumpKey;
    SpriteObject m_LeftKey;
    SpriteObject m_RightKey;
    SpriteObject m_OpenKey;
};
} // Platformer

#endif // PLATFORMER_EDITOR_FIRST_LEVEL_HPP
