#ifndef PLATFORMER_GAME_DOOR_HPP
#define PLATFORMER_GAME_DOOR_HPP

#include "Blueprint/Resources/TextureManager.hpp"
#include "nlohmann/json.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Platformer {
class CastleLevel;
class Door {
public:
    Door();

public:
    void load(const nlohmann::ordered_json& data);
    void render(sf::RenderTarget& renderTarget);

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);

    void setTileIndex(const sf::Vector2i& tilePosition);

    [[nodiscard]] sf::FloatRect getBoundingBox() const;

private:
    Blueprint::Resources::TextureResource m_Resource;
    sf::RectangleShape m_RectangleShape;
};
} // Platformer

#endif // PLATFORMER_GAME_DOOR_HPP
