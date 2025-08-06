#ifndef PLATFORMER_EDITOR_CASTLE_LEVEL_HPP
#define PLATFORMER_EDITOR_CASTLE_LEVEL_HPP

#include "ItemPreview.hpp"
#include "SpriteObject.hpp"
#include "SceneEditor.hpp"
#include "Platformer/TilesHolder.hpp"

namespace Platformer {
class CastleLevel final : public SceneEditor {
public:
    CastleLevel();

private:
    void load(const nlohmann::ordered_json& data) override;
    void loadPalette();
    void loadBackground(const nlohmann::ordered_json& data);
    void loadGround(const nlohmann::ordered_json& data);
    void loadBlocks(const nlohmann::ordered_json& data);
    void loadPlayer(const nlohmann::ordered_json& data);
    void loadDoor(const nlohmann::ordered_json& data);
    void loadStopCameraTrigger(const nlohmann::ordered_json& data);

    void save(nlohmann::ordered_json& data) override;

    void update() override;
    void updateViewLimit();
    void updateItemPreviewIcon();
    void updateItemPreview();
    void updateAdd();
    void updateRemove();
    void updateRemoveTiles(TilesHolder& tilesHolder);
    void updateSpriteObject(SpriteObject& spriteObject, const char* itemName);
    void updateStopCameraTrigger();

    void render(sf::RenderTarget& renderTarget) override;

    [[nodiscard]] Blueprint::Editor::Palette* getPalette() override;

private:
    const sf::Color m_BackgroundColor;
    Blueprint::Editor::Palette m_Palette;
    const Blueprint::Editor::Palette::Item* m_LastItem;
    ItemPreview m_ItemPreview;

    TilesHolder m_BackGroundHolder;
    TilesHolder m_GroundHolder;
    TilesHolder m_BlocksHolder;
    SpriteObject m_Player;
    SpriteObject m_Door;
    SpriteObject m_StopCameraTrigger;

    sf::Vector2f m_DragStart;
    TilesHolder::Tile* m_Tile;
};
} // Platformer

#endif // PLATFORMER_EDITOR_CASTLE_LEVEL_HPP
