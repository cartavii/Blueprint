#ifndef PLATFORMER_EDITOR_SPRITE_OBJECT_HPP
#define PLATFORMER_EDITOR_SPRITE_OBJECT_HPP

#include "Blueprint/Resources/TextureManager.hpp"

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Platformer {
class SpriteObject {
public:
    SpriteObject();

public:
    void load(const nlohmann::ordered_json& data);
    void save(nlohmann::ordered_json& data);

    void render(sf::RenderTarget& renderTarget);

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);
    const Blueprint::Resources::TextureResource& getTextureResource() const;

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setSize(const sf::Vector2f& size);
    [[nodiscard]] sf::Vector2f getSize() const;

    void setTextureIndex(const sf::Vector2i& textureIndex);
    [[nodiscard]] sf::Vector2i getTextureIndex() const;

private:
    sf::RectangleShape m_RectangleShape;
    Blueprint::Resources::TextureResource m_TextureResource;
};
} // Platformer

#endif // PLATFORMER_EDITOR_SPRITE_OBJECT_HPP
