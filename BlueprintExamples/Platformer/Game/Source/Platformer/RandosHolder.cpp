#include "Platformer/RandosHolder.hpp"
#include "Platformer/CastleLevel.hpp"

#include "Blueprint/Game/Application.hpp"

Platformer::RandosHolder::RandosHolder(CastleLevel& castleLevel) : m_CastleLevel(castleLevel) {}

Platformer::RandosHolder::~RandosHolder() {
    for (const Rando* rando : m_Randos) {
        delete rando;
    }
}

void Platformer::RandosHolder::load(const nlohmann::ordered_json& data) {
    auto& textureManager = m_CastleLevel.getSceneManager().getApplication().getTextureManager();
    m_Resource = textureManager.getTextureResource("Rando.png");
    for (const nlohmann::ordered_json& randoData : data) {
        Rando* rando = new Rando(m_CastleLevel);
        rando->load(randoData);
        rando->setTextureResource(m_Resource);
        m_Randos.push_back(rando);
    }
}

void Platformer::RandosHolder::update(const float deltaTime) {
    for (Rando* rando : m_Randos) {
        rando->update(deltaTime);
    }
}

void Platformer::RandosHolder::render(sf::RenderTarget& renderTarget) {
    for (Rando* rando : m_Randos) {
        rando->render(renderTarget);
    }
    for (Rando* rando : m_Randos) {
        rando->getMessage().render(renderTarget);
    }
}
