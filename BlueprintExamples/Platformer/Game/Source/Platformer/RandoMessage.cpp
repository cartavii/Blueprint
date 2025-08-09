#include "Platformer/RandoMessage.hpp"
#include "Platformer/CastleLevel.hpp"
#include "Platformer/Random.hpp"
#include "Blueprint/Game/Application.hpp"

Platformer::RandoMessage::RandoMessage(CastleLevel& castleLevel)
: SpriteObject(sf::Vector2f(16.f, 16.f))
, m_CastleLevel(castleLevel)
, m_FadeInDuration(5.f)
, m_StayDuration(30.f)
, m_FadeOutDuration(5.f)
, m_VerticalSpeed(-0.2f)
, m_Elapsed(100.f) {}

void Platformer::RandoMessage::load(const nlohmann::ordered_json& data) {
    auto& textureManager = m_CastleLevel.getSceneManager().getApplication().getTextureManager();
    m_Resource[0] = textureManager.getTextureResource("BD.png");
    m_Resource[1] = textureManager.getTextureResource("GG.png");
    m_Resource[2] = textureManager.getTextureResource("Heart.png");
    m_Resource[3] = textureManager.getTextureResource("NY.png");
    setTextureResource(m_Resource[0]);
}

void Platformer::RandoMessage::initialize(const sf::Vector2f& startingPosition) {
    setPosition(startingPosition);
    m_Elapsed = 0.f;
    setTextureResource(m_Resource[static_cast<std::size_t>(Random::randomRange(0.f, 3.9f))]);
}

void Platformer::RandoMessage::update(const float deltaTime) {
    sf::RectangleShape& rectangle = getRectangle();
    float progress = 0.f;
    m_Elapsed += deltaTime;
    if (m_Elapsed < m_FadeInDuration) {
        progress = m_Elapsed / m_FadeInDuration;
    } else if (const float localDuration = m_FadeInDuration + m_StayDuration; m_Elapsed < localDuration) {
        progress = 1.f;
    } else if (const float totalDuration = m_FadeInDuration + m_StayDuration + m_FadeOutDuration; m_Elapsed < totalDuration) {
        progress = 1.f - m_Elapsed / m_FadeInDuration;
    }
    rectangle.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(progress * 255.f)));
    rectangle.move(sf::Vector2f(0.f, m_VerticalSpeed * deltaTime));
}

bool Platformer::RandoMessage::isElapsed() const {
    return m_Elapsed >= m_FadeInDuration + m_StayDuration + m_FadeOutDuration;
}
