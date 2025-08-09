#include "Platformer/FirstLevel.hpp"
#include "Platformer/Loader.hpp"

#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/SceneManager.hpp"

Platformer::FirstLevel::FirstLevel(Blueprint::Game::SceneManager& manager)
: CastleLevel(manager)
, m_HintDuration(20.f)
, m_HintDistance(3.f)
, m_HintSpace(4.f)
, m_JumpHint(sf::Vector2f(16.f * 3.f, 16.f), m_HintDuration, m_HintDistance)
, m_LeftHint(sf::Vector2f(16.f, 16.f), m_HintDuration, m_HintDistance)
, m_RightHint(sf::Vector2f(16.f, 16.f), m_HintDuration, m_HintDistance)
, m_DownHint(sf::Vector2f(16.f, 16.f), m_HintDuration, m_HintDistance) {}

void Platformer::FirstLevel::load(const nlohmann::ordered_json& data) {
    CastleLevel::load(data);
    Blueprint::Resources::TextureManager& textureManager = getSceneManager().getApplication().getTextureManager();
    m_JumpHint.setTextureResource(textureManager.getTextureResource("Movement.png"));
    m_LeftHint.setTextureResource(textureManager.getTextureResource("Movement.png"));
    m_RightHint.setTextureResource(textureManager.getTextureResource("Movement.png"));
    m_DownHint.setTextureResource(textureManager.getTextureResource("Open.png"));
    m_LeftHint.setTileIndex(sf::Vector2i(3, 0));
    m_RightHint.setTileIndex(sf::Vector2i(4, 0));
    if (data.contains("Movement")) {
        m_JumpHint.setPosition(Loader::loadVector2f(data["Movement"], "Position"));
    }
    const sf::Vector2f space(m_HintSpace, 0.f);
    m_LeftHint.setPosition(m_JumpHint.getPosition() + sf::Vector2f(m_JumpHint.getTileSize().x, 0.f) + space);
    m_RightHint.setPosition(m_LeftHint.getPosition() + sf::Vector2f(m_LeftHint.getTileSize().x, 0.f) + space);
    if (data.contains("Open")) {
        m_DownHint.setPosition(Loader::loadVector2f(data["Open"], "Position"));
    }
}

void Platformer::FirstLevel::update(const sf::Time& deltaTime) {
    CastleLevel::update(deltaTime);
    const float dt = deltaTime.asSeconds() * 60.f;
    m_JumpHint.update(dt);
    m_LeftHint.update(dt);
    m_RightHint.update(dt);
    m_DownHint.update(dt);
}

void Platformer::FirstLevel::render(sf::RenderTarget& renderTarget) {
    CastleLevel::render(renderTarget);
    m_JumpHint.render(renderTarget);
    m_LeftHint.render(renderTarget);
    m_RightHint.render(renderTarget);
    m_DownHint.render(renderTarget);
    m_Player.render(renderTarget);
}

