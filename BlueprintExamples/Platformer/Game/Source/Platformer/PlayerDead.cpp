#include "Platformer/PlayerDead.hpp"
#include "Platformer/Camera.hpp"
#include "Platformer/CastleLevel.hpp"
#include "Platformer/Random.hpp"

#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/SceneManager.hpp"

Platformer::PlayerDead::PlayerDead(CastleLevel& castleLevel)
: SpriteObject(sf::Vector2f(16.f, 16.f))
, m_CastleLevel(castleLevel)
, m_Camera(castleLevel.getCamera())
, m_Rectangle(getRectangle())
, m_VerticalSpeed(-4.f)
, m_Gravity(0.2f)
, m_RotationSpeed(Random::randomRange(-2.f, 2.f))
, m_TimeElapsed(0.f)
, m_RestartTime(80.f) {
    Blueprint::Resources::TextureManager& textureManager = castleLevel.getSceneManager().getApplication().getTextureManager();
    m_Resource = textureManager.getTextureResource("Gorl/Dead.png");
    setTextureResource(m_Resource);
    m_Rectangle.setOrigin(sf::Vector2f(8.f, 8.f));
}

void Platformer::PlayerDead::update(const float deltaTime) {
    m_VerticalSpeed += m_Gravity * deltaTime;
    m_TimeElapsed += deltaTime;
    if (m_TimeElapsed >= m_RestartTime) {
        m_CastleLevel.restartScene();
    }
    m_Rectangle.move(sf::Vector2f(0.f, m_VerticalSpeed * deltaTime));
    m_Rectangle.rotate(sf::degrees(m_RotationSpeed * deltaTime));
    m_Camera.setCenter(sf::Vector2f(getPosition().x, m_CastleLevel.getCamera().getCenter().y));
}
