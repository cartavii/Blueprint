#include "Platformer/HedgehogsHolder.hpp"
#include "Platformer/CastleLevelExt.hpp"
#include "Platformer/HintHog.hpp"
#include "Blueprint/Game/Application.hpp"

Platformer::HedgehogsHolder::HedgehogsHolder(CastleLevelExt& castleLevel)
: m_CastleLevel(castleLevel) {}

void Platformer::HedgehogsHolder::load(const nlohmann::ordered_json& data) {
    loadResources();
    if (data.contains("Hedgehogs")) {
        loadHedgehogs(data);
    }
    if (data.contains("HintHogs")) {
        loadHintHogs(data);
    }
}

void Platformer::HedgehogsHolder::loadResources() {
    auto& textureManager = m_CastleLevel.getSceneManager().getApplication().getTextureManager();
    m_Resource           = textureManager.getTextureResource("Hedgehog.png");
    m_HintResource       = textureManager.getTextureResource("Hint.png");
}

void Platformer::HedgehogsHolder::loadHedgehogs(const nlohmann::ordered_json& data) {
    for (const nlohmann::ordered_json& hedgehogData: data["Hedgehogs"]) {
        Hedgehog* hedgehog = new Hedgehog(m_CastleLevel);
        hedgehog->load(hedgehogData);
        hedgehog->setTextureResource(m_Resource);
        m_Hedgehogs.push_back(hedgehog);
    }
}

void Platformer::HedgehogsHolder::loadHintHogs(const nlohmann::ordered_json& data) {
    for (const nlohmann::ordered_json& hedgehogData: data["HintHogs"]) {
        HintHog* hedgehog = new HintHog(m_CastleLevel);
        hedgehog->load(hedgehogData);
        hedgehog->setTextureResource(m_Resource);
        hedgehog->getHint().setTextureResource(m_HintResource);
        m_Hedgehogs.push_back(hedgehog);
    }
}

void Platformer::HedgehogsHolder::update(const float deltaTime) {
    for (Hedgehog* hedgehog: m_Hedgehogs) {
        hedgehog->update(deltaTime);
    }
}

void Platformer::HedgehogsHolder::render(sf::RenderTarget& renderTarget) {
    for (Hedgehog* hedgehog: m_Hedgehogs) {
        hedgehog->render(renderTarget);
    }
}
