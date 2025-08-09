#include "Platformer/LastLevel.hpp"

Platformer::LastLevel::LastLevel(Blueprint::Game::SceneManager& manager)
: CastleLevel(manager)
, m_Randos(*this) {}

void Platformer::LastLevel::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    if (data.contains("Randos")) {
        m_Randos.load(data["Randos"]);
    }
}

void Platformer::LastLevel::update(const sf::Time& deltaTime) {
    CastleLevel::update(deltaTime);
    const float dt = deltaTime.asSeconds() * 60.f;
    m_Randos.update(dt);
}

void Platformer::LastLevel::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_Randos.render(renderTarget);
    m_Player.render(renderTarget);
}
