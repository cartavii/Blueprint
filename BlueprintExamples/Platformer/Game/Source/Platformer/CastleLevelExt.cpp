#include "Platformer/CastleLevelExt.hpp"

Platformer::CastleLevelExt::CastleLevelExt(Blueprint::Game::SceneManager& manager)
: CastleLevel(manager)
, m_HedgehogsHolder(*this) {}

void Platformer::CastleLevelExt::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    m_HedgehogsHolder.load(data);
}


void Platformer::CastleLevelExt::update(const sf::Time& deltaTime) {
    CastleLevel::update(deltaTime);
    const float dt = deltaTime.asSeconds() * 60.f;
    m_HedgehogsHolder.update(dt);
}

void Platformer::CastleLevelExt::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_HedgehogsHolder.render(renderTarget);
}


