#include "Platformer/CastleLevelExt.hpp"

#include <SFML/Window/Mouse.hpp>

void Platformer::CastleLevelExt::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    loadPalette();
    loadHedgehogs(data);
    loadHintHogs(data);
}

void Platformer::CastleLevelExt::loadPalette() {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_Palette.addItem({textureManager.getTextureResource("Icons/Hedgehog.png"), "Hedgehog"});
    m_Palette.addItem({textureManager.getTextureResource("Icons/HintHog.png"), "HintHog"});
}

void Platformer::CastleLevelExt::loadHedgehogs(const nlohmann::ordered_json& data) {
    m_Hedgehogs.setTextureResource(getTextureManager().getTextureResource("Icons/Hedgehog.png"));
    if (data.contains("Hedgehogs")) {
        m_Hedgehogs.load(data["Hedgehogs"]);
    }
}

void Platformer::CastleLevelExt::loadHintHogs(const nlohmann::ordered_json& data) {
    m_HintHogs.setTextureResource(getTextureManager().getTextureResource("Icons/HintHog.png"));
    if (data.contains("HintHogs")) {
        m_HintHogs.load(data["HintHogs"]);
    }
}

void Platformer::CastleLevelExt::save(nlohmann::ordered_json& data) {
    CastleLevel::save(data);
    m_Hedgehogs.save(data["Hedgehogs"]);
    m_HintHogs.save(data["HintHogs"]);
}

void Platformer::CastleLevelExt::update() {
    CastleLevel::update();
    if (m_LastItem == nullptr) {
        return;
    }
    if (!isMouseInsideScreen()) {
        return;
    }
    if (m_LastItem->name == "Hedgehog") {
        updateHedgehogsAdd();
        updateHedgehogsRemove();
    } else if (m_LastItem->name == "HintHog") {
        updateHintHogsAdd();
        updateHintHogsRemove();
    }
}

void Platformer::CastleLevelExt::updateHedgehogsAdd() {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return;
    }
    m_Hedgehogs.updateAdd(getMouseTilePosition());
}

void Platformer::CastleLevelExt::updateHedgehogsRemove() {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        return;
    }
    m_Hedgehogs.updateRemove(getMouseTilePosition());
}

void Platformer::CastleLevelExt::updateHintHogsAdd() {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return;
    }
    m_HintHogs.updateAdd(getMouseTilePosition());
}

void Platformer::CastleLevelExt::updateHintHogsRemove() {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        return;
    }
    m_HintHogs.updateRemove(getMouseTilePosition());
}

void Platformer::CastleLevelExt::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_Hedgehogs.render(renderTarget);
    m_HintHogs.render(renderTarget);
}
