#ifndef PLATFORMER_GAME_SPRITE_OBJECT_HPP
#define PLATFORMER_GAME_SPRITE_OBJECT_HPP

#include "Blueprint/Resources/TextureManager.hpp"
#include "nlohmann/json.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Platformer {
class SpriteObject {
public:
    explicit SpriteObject(const sf::Vector2f& tileSize);
    virtual ~SpriteObject() = default;

public:
    virtual void load(const nlohmann::ordered_json& data) {};

    void render(sf::RenderTarget& renderTarget);

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);

    void setTileSize(const sf::Vector2f& tileSize);
    [[nodiscard]] sf::Vector2f getTileSize() const;

    void setTileIndex(sf::Vector2i tileIndex);
    [[nodiscard]] sf::Vector2i getTileIndex() const;

protected:
    [[nodiscard]] sf::RectangleShape& getRectangle();
    [[nodiscard]] const sf::RectangleShape& getRectangle() const;

private:
    sf::RectangleShape m_Rectangle;
    sf::Vector2i m_TileSize;
};
} // Platformer

#endif // PLATFORMER_GAME_SPRITE_OBJECT_HPP
