#include "Platformer/FirstLevel.hpp"
#include "Platformer/Saver.hpp"

#include "SFML/Window/Mouse.hpp"

Platformer::FirstLevel::FirstLevel() : m_KeySpace(4.f) {}

void Platformer::FirstLevel::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    loadPalette();
    loadMovementKeys(data);
    loadOpenKey(data);
}

void Platformer::FirstLevel::loadPalette() {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_Palette.addItem({textureManager.getTextureResource("Icons/Open.png"), "Open Key"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/Movement.png"), "Movement Keys"});
}

void Platformer::FirstLevel::loadMovementKeys(const nlohmann::ordered_json& data) {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    const Blueprint::Resources::TextureResource resource = textureManager.getTextureResource("Movement.png");
    m_JumpKey.setTextureResource(resource);
    m_LeftKey.setTextureResource(resource);
    m_RightKey.setTextureResource(resource);
    m_JumpKey.setSize(sf::Vector2f(48.f, 16.f));
    m_LeftKey.setTextureIndex(sf::Vector2i(3, 0));
    m_RightKey.setTextureIndex(sf::Vector2i(4, 0));
    if (!data.contains("Movement")) {
        return setMovementPosition({});
    }
    m_JumpKey.load(data["Movement"]);
    setMovementPosition(m_JumpKey.getPosition());
}

void Platformer::FirstLevel::loadOpenKey(const nlohmann::ordered_json& data) {
    m_OpenKey.setTextureResource(getTextureManager().getTextureResource("Open.png"));
    if (data.contains("Open")) {
        m_OpenKey.load(data["Open"]);
    }
}

void Platformer::FirstLevel::save(nlohmann::ordered_json& data) {
    CastleLevel::save(data);
    saveMovementKeys(data);
    saveOpenKey(data);
}

void Platformer::FirstLevel::saveMovementKeys(nlohmann::ordered_json& data) {
    Saver::saveVector2f(data["Movement"], m_JumpKey.getPosition(), "Position");
}

void Platformer::FirstLevel::saveOpenKey(nlohmann::ordered_json& data) {
    Saver::saveVector2f(data["Open"], m_OpenKey.getPosition(), "Position");
}

void Platformer::FirstLevel::update() {
    CastleLevel::update();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isMouseInsideScreen()) {
        updateMovementPosition();
        updateOpenPosition();
    }
}

void Platformer::FirstLevel::updateMovementPosition() {
    if (m_LastItem == nullptr || m_LastItem->name != "Movement Keys") {
        return;
    }
    setMovementPosition(getMouseTilePosition());
}

void Platformer::FirstLevel::setMovementPosition(sf::Vector2f topLeft) {
    m_JumpKey.setPosition(topLeft);
    topLeft.x += m_JumpKey.getSize().x + m_KeySpace;
    m_LeftKey.setPosition(topLeft);
    topLeft.x += m_LeftKey.getSize().x + m_KeySpace;
    m_RightKey.setPosition(topLeft);
}

void Platformer::FirstLevel::updateOpenPosition() {
    if (m_LastItem == nullptr || m_LastItem->name != "Open Key") {
        return;
    }
    m_OpenKey.setPosition(getMouseTilePosition());
}

void Platformer::FirstLevel::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_JumpKey.render(renderTarget);
    m_LeftKey.render(renderTarget);
    m_RightKey.render(renderTarget);
    m_OpenKey.render(renderTarget);
}
