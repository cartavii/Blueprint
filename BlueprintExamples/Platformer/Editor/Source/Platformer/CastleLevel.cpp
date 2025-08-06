#include "Platformer/CastleLevel.hpp"

#include <SFML/Window/Mouse.hpp>

Platformer::CastleLevel::CastleLevel()
: m_BackgroundColor(25, 2, 25)
, m_LastItem(nullptr)
, m_Tile(nullptr) {
    sf::View& view = getView();
    view.setSize(sf::Vector2f(192.f, 144.f));
    view.setCenter(view.getSize() / 2.f);
}

void Platformer::CastleLevel::load(const nlohmann::ordered_json& data) {
    loadPalette();
    loadBackground(data);
    loadGround(data);
    loadBlocks(data);
    loadPlayer(data);
    loadDoor(data);
    loadStopCameraTrigger(data);
}

void Platformer::CastleLevel::loadPalette() {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_Palette.addItem({textureManager.getTextureResource("Icons/Gorl.png"), "Gorl"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/Back Ground.png"), "Back Ground"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/Ground.png"), "Ground"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/Block.png"), "Block"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/Door.png"), "Door"});
    m_Palette.addItem({textureManager.getTextureResource("Triggers/StopCam.png"), "StopCam", {{0, 0,}, {32, 32}}});
}

void Platformer::CastleLevel::loadBackground(const nlohmann::ordered_json& data) {
    m_BackGroundHolder.setTextureResource(getTextureManager().getTextureResource("Back Ground.png"));
    if (!data.contains("BackGroundTiles")) {
        return;
    }
    m_BackGroundHolder.load(data["BackGroundTiles"]);
}

void Platformer::CastleLevel::loadGround(const nlohmann::ordered_json& data) {
    m_GroundHolder.setTextureResource(getTextureManager().getTextureResource("Ground.png"));
    if (!data.contains("GroundTiles")) {
        return;
    }
    m_GroundHolder.load(data["GroundTiles"]);
}

void Platformer::CastleLevel::loadBlocks(const nlohmann::ordered_json& data) {
    m_BlocksHolder.setTextureResource(getTextureManager().getTextureResource("Block.png"));
    if (!data.contains("BlockTiles")) {
        return;
    }
    m_BlocksHolder.load(data["BlockTiles"]);
}

void Platformer::CastleLevel::loadPlayer(const nlohmann::ordered_json& data) {
    m_Player.setTextureResource(getTextureManager().getTextureResource("Gorl/Idle.png"));
    if (data.contains("Player")) {
        m_Player.load(data["Player"]);
    }
}

void Platformer::CastleLevel::loadDoor(const nlohmann::ordered_json& data) {
    m_Door.setTextureResource(getTextureManager().getTextureResource("Door.png"));
    m_Door.setSize(sf::Vector2f(16.f, 16.f));
    if (data.contains("Door")) {
        m_Door.load(data["Door"]);
    }
}

void Platformer::CastleLevel::loadStopCameraTrigger(const nlohmann::ordered_json& data) {
    m_StopCameraTrigger.setTextureResource(getTextureManager().getTextureResource("Triggers/StopCam.png"));
    if (data.contains("StopCamera")) {
        m_StopCameraTrigger.setPosition(sf::Vector2f(data["StopCamera"].get<float>(), 0.f));
    }
}

void Platformer::CastleLevel::save(nlohmann::ordered_json& data) {
    m_BackGroundHolder.save(data["BackGroundTiles"]);
    m_GroundHolder.save(data["GroundTiles"]);
    m_BlocksHolder.save(data["BlockTiles"]);
    m_Player.save(data["Player"]);
    m_Door.save(data["Door"]);
    data["StopCamera"] = m_StopCameraTrigger.getPosition().x;
}

void Platformer::CastleLevel::update() {
    SceneEditor::update();
    updateViewLimit();
    if (const Blueprint::Editor::Palette::Item* selectedItem = m_Palette.getSelectedItem();
        selectedItem != m_LastItem) {
        m_LastItem = selectedItem;
        updateItemPreviewIcon();
    }
    updateItemPreview();
    updateAdd();
    updateRemove();
    updateSpriteObject(m_Player, "Gorl");
    updateSpriteObject(m_Door, "Door");
    updateStopCameraTrigger();
}

void Platformer::CastleLevel::updateViewLimit() {
    sf::View& view = getView();
    const sf::Vector2f viewSize = view.getSize();
    if (view.getCenter().y != viewSize.y / 2.f) {
        view.setCenter(sf::Vector2f(view.getCenter().x, viewSize.y / 2.f));
    }
    if (view.getCenter().x < viewSize.x / 2.f) {
        view.setCenter(sf::Vector2f(viewSize.x / 2.f, view.getCenter().y));
    }
}

void Platformer::CastleLevel::updateItemPreviewIcon() {
    if (m_LastItem == nullptr) {
        return m_ItemPreview.reset();
    }
    m_ItemPreview.setTextureResource(m_LastItem->textureResource);
    sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(16, 16));
    if (m_LastItem->textureRect != sf::IntRect{}) {
        textureRect = m_LastItem->textureRect;
    }
    m_ItemPreview.setTextureRect(textureRect);
}

void Platformer::CastleLevel::updateItemPreview() {
    m_ItemPreview.setPosition(getMouseTilePosition());
}

void Platformer::CastleLevel::updateAdd() {
    if (m_LastItem == nullptr) {
        return;
    }
    const sf::Vector2f mouseTilePosition = getMouseTilePosition();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (m_Tile == nullptr && isMouseInsideScreen()) {
            if (m_LastItem->name == "Back Ground") {
                m_Tile = &m_BackGroundHolder.addTile(m_DragStart, m_DragStart);
            } else if (m_LastItem->name == "Ground") {
                m_Tile = &m_GroundHolder.addTile(m_DragStart, m_DragStart);
            } else if (m_LastItem->name == "Block") {
                m_Tile = &m_BlocksHolder.addTile(m_DragStart, m_DragStart);
            } else {
                return;
            }
            m_DragStart = mouseTilePosition;
            m_ItemPreview.reset();
        }
        if (m_Tile == nullptr) {
            return;
        }
        sf::Vector2f size = m_DragStart - mouseTilePosition;
        size.x = std::abs(size.x);
        size.y = std::abs(size.y);
        const sf::Vector2f topLeft(std::min(m_DragStart.x, mouseTilePosition.x), std::min(m_DragStart.y, mouseTilePosition.y));
        const sf::Vector2f bottomRight = topLeft + size + sf::Vector2f(16.f, 16.f);
        m_Tile->topLeft = topLeft;
        m_Tile->bottomRight = bottomRight;
    } else {
        m_Tile = nullptr;
        updateItemPreviewIcon();
    }
}

void Platformer::CastleLevel::updateRemove() {
    if (m_LastItem == nullptr) {
        return;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && isMouseInsideScreen()) {
        if (m_LastItem->name == "Back Ground") {
            updateRemoveTiles(m_BackGroundHolder);
        } else if (m_LastItem->name == "Ground") {
            updateRemoveTiles(m_GroundHolder);
        } else if (m_LastItem->name == "Block") {
            updateRemoveTiles(m_BlocksHolder);
        }
    }
}

void Platformer::CastleLevel::updateRemoveTiles(TilesHolder& tilesHolder) {
    const sf::Vector2f mousePosition = getMouseViewPosition(getView());
    for (TilesHolder::iterator it = tilesHolder.begin(); it != tilesHolder.end(); ++it) {
        if (const sf::FloatRect boundingBox(it->topLeft, it->bottomRight - it->topLeft);
        boundingBox.contains(mousePosition)) {
            it = tilesHolder.removeTile(it);
            if (it == tilesHolder.end()) {
                return;
            }
        }
    }
}

void Platformer::CastleLevel::updateSpriteObject(SpriteObject& spriteObject, const char* itemName) {
    if (m_LastItem == nullptr || m_LastItem->name != itemName) {
        return;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return;
    }
    if (!isMouseInsideScreen()) {
        return;
    }
    spriteObject.setPosition(getMouseTilePosition());
}

void Platformer::CastleLevel::updateStopCameraTrigger() {
    if (m_LastItem == nullptr || m_LastItem->name != "StopCam") {
        return;
    }
    m_ItemPreview.setPosition(sf::Vector2f(m_ItemPreview.getPosition().x, 0.f));
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return;
    }
    if (!isMouseInsideScreen()) {
        return;
    }
    m_StopCameraTrigger.setPosition(m_ItemPreview.getPosition());
}

void Platformer::CastleLevel::render(sf::RenderTarget& renderTarget) {
    SceneEditor::render(renderTarget);
    renderTarget.clear(m_BackgroundColor);
    m_BackGroundHolder.render(renderTarget);
    m_GroundHolder.render(renderTarget);
    m_BlocksHolder.render(renderTarget);
    m_Door.render(renderTarget);
    m_Player.render(renderTarget);
    m_StopCameraTrigger.render(renderTarget);
    if (isMouseInsideScreen()) {
        m_ItemPreview.render(renderTarget);
    }
}

Blueprint::Editor::Palette* Platformer::CastleLevel::getPalette() {
    return &m_Palette;
}
