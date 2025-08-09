#include "Platformer/LastLevel.hpp"

#include "SFML/Window/Mouse.hpp"

void Platformer::LastLevel::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    loadPalette();
    loadRandos(data);
}

void Platformer::LastLevel::loadPalette() {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_Palette.addItem({textureManager.getTextureResource("Icons/Rando.png"), "Rando"});
}

void Platformer::LastLevel::loadRandos(const nlohmann::ordered_json& data) {
    m_RandoHolder.setTextureResource(getTextureManager().getTextureResource("Rando.png"));
    if (data.contains("Randos")) {
        m_RandoHolder.load(data["Randos"]);
    }
}

void Platformer::LastLevel::save(nlohmann::ordered_json& data) {
    CastleLevel::save(data);
    m_RandoHolder.save(data["Randos"]);
}

void Platformer::LastLevel::update() {
    CastleLevel::update();
    updateRandoAdd();
    updateRandoRemove();
}

void Platformer::LastLevel::updateRandoAdd() {
    if (m_LastItem == nullptr || m_LastItem->name != "Rando") {
        return;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || !isMouseInsideScreen()) {
        return;
    }
    m_RandoHolder.updateAdd(getMouseTilePosition());
}

void Platformer::LastLevel::updateRandoRemove() {
    if (m_LastItem == nullptr || m_LastItem->name != "Rando") {
        return;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || !isMouseInsideScreen()) {
        return;
    }
    m_RandoHolder.updateRemove(getMouseTilePosition());
}

void Platformer::LastLevel::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_RandoHolder.render(renderTarget);
}
