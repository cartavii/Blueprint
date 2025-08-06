#ifndef PLATFORMER_EDITOR_ITEM_PREVIEW_HPP
#define PLATFORMER_EDITOR_ITEM_PREVIEW_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "Blueprint/Resources/TextureManager.hpp"

namespace Platformer {
class ItemPreview {
public:
    ItemPreview();

public:
    void render(sf::RenderTarget& renderTarget);
    void reset();

    void setTileIndex(const sf::Vector2i& tileIndex);
    [[nodiscard]] sf::Vector2i getTileIndex() const;

    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);
    [[nodiscard]] const Blueprint::Resources::TextureResource& getTextureResource();

    void setTextureRect(const sf::IntRect& textureRect);
    [[nodiscard]] const sf::IntRect& getTextureRect() const;

private:
    Blueprint::Resources::TextureResource m_TextureResource;
    sf::RectangleShape m_RectangleShape;
};
} // Platformer

#endif // PLATFORMER_EDITOR_ITEM_PREVIEW_HPP
