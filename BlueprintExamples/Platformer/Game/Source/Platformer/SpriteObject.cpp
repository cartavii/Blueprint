#include "Platformer/SpriteObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Platformer::SpriteObject::SpriteObject(const sf::Vector2f& tileSize)
: m_Rectangle(tileSize)
, m_TileSize(tileSize) {
    setTileIndex(sf::Vector2i(0, 0));
}

void Platformer::SpriteObject::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_Rectangle);
}

void Platformer::SpriteObject::setPosition(const sf::Vector2f& position) {
    m_Rectangle.setPosition(position);
}

sf::Vector2f Platformer::SpriteObject::getPosition() const {
    return m_Rectangle.getPosition();
}

void Platformer::SpriteObject::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_Rectangle.setTexture(textureResource.getTexture());
}

void Platformer::SpriteObject::setTileSize(const sf::Vector2f& tileSize) {
    const sf::Vector2i oldTileIndex = getTileIndex();
    m_Rectangle.setSize(tileSize);
    m_TileSize = sf::Vector2i(tileSize);
    setTileIndex(oldTileIndex);
}

sf::Vector2f Platformer::SpriteObject::getTileSize() const {
    return m_Rectangle.getSize();
}

void Platformer::SpriteObject::setTileIndex(sf::Vector2i tileIndex) {
    tileIndex.x *= m_TileSize.x;
    tileIndex.y *= m_TileSize.y;
    m_Rectangle.setTextureRect(sf::IntRect(tileIndex, m_TileSize));
}

sf::Vector2i Platformer::SpriteObject::getTileIndex() const {
    sf::Vector2i tileIndex = m_Rectangle.getTextureRect().position;
    tileIndex.x /= m_TileSize.x;
    tileIndex.y /= m_TileSize.y;
    return tileIndex;
}

sf::RectangleShape& Platformer::SpriteObject::getRectangle() {
    return m_Rectangle;
}

const sf::RectangleShape& Platformer::SpriteObject::getRectangle() const {
    return m_Rectangle;
}

