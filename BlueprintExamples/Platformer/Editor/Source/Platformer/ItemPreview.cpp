#include "Platformer/ItemPreview.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Platformer::ItemPreview::ItemPreview() : m_RectangleShape(sf::Vector2f(16.f, 16.f)) {
    m_RectangleShape.setFillColor(sf::Color(255, 255, 255, 100));
}

void Platformer::ItemPreview::render(sf::RenderTarget& renderTarget) {
    if (m_TextureResource.getTexture() != nullptr) {
        renderTarget.draw(m_RectangleShape);
    }
}

void Platformer::ItemPreview::reset() {
    m_TextureResource = {};
    setTileIndex(sf::Vector2i());
}

void Platformer::ItemPreview::setTileIndex(const sf::Vector2i& tileIndex) {
    m_RectangleShape.setTextureRect(sf::IntRect(tileIndex * 16, sf::Vector2i(16, 16)));
}

sf::Vector2i Platformer::ItemPreview::getTileIndex() const {
    return m_RectangleShape.getTextureRect().position / 16;
}

void Platformer::ItemPreview::setPosition(const sf::Vector2f& position) {
    m_RectangleShape.setPosition(position);
}

sf::Vector2f Platformer::ItemPreview::getPosition() const {
    return m_RectangleShape.getPosition();
}

void Platformer::ItemPreview::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_TextureResource = textureResource;
    m_RectangleShape.setTexture(m_TextureResource.getTexture());
}

const Blueprint::Resources::TextureResource& Platformer::ItemPreview::getTextureResource() {
    return m_TextureResource;
}

void Platformer::ItemPreview::setTextureRect(const sf::IntRect& textureRect) {
    m_RectangleShape.setTextureRect(textureRect);
}

const sf::IntRect& Platformer::ItemPreview::getTextureRect() const {
    return m_RectangleShape.getTextureRect();
}
