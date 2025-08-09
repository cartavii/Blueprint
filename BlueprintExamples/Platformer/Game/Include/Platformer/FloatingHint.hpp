#ifndef PLATFORMER_GAME_FLOATING_HINT_HPP
#define PLATFORMER_GAME_FLOATING_HINT_HPP

#include "Platformer/SpriteObject.hpp"

namespace Platformer {
class FloatingHint final : public SpriteObject {
public:
    FloatingHint(const sf::Vector2f& tileSize, float duration, float distance);

public:
    void update(float deltaTime);

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] const sf::Vector2f& getPosition() const;

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);

private:
    Blueprint::Resources::TextureResource m_Resource;
    const float m_Duration;
    const float m_Distance;
    float m_Elapsed;
    sf::Vector2f m_Position;
};
} // Platformer

#endif // PLATFORMER_GAME_FLOATING_HINT_HPP
