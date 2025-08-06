#include "Platformer/SpriteObject.hpp"
#include "Platformer/Loader.hpp"
#include "Platformer/Saver.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Platformer::SpriteObject::SpriteObject() : m_RectangleShape(sf::Vector2f(16.f, 16.f)) {}

void Platformer::SpriteObject::load(const nlohmann::ordered_json& data) {
    if (!data.contains("Position")) {
        return;
    }
    m_RectangleShape.setPosition(Loader::loadVector2f(data, "Position"));
}

void Platformer::SpriteObject::save(nlohmann::ordered_json& data) {
    Saver::saveVector2f(data, m_RectangleShape.getPosition(), "Position");
}

void Platformer::SpriteObject::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_RectangleShape);
}

void Platformer::SpriteObject::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_TextureResource = textureResource;
    m_RectangleShape.setTexture(m_TextureResource.getTexture());
}

const Blueprint::Resources::TextureResource& Platformer::SpriteObject::getTextureResource() const {
    return m_TextureResource;
}

void Platformer::SpriteObject::setPosition(const sf::Vector2f& position) {
    m_RectangleShape.setPosition(position);
}

sf::Vector2f Platformer::SpriteObject::getPosition() const {
    return m_RectangleShape.getPosition();
}

void Platformer::SpriteObject::setSize(const sf::Vector2f& size) {
    const sf::Vector2i textureIndex = getTextureIndex();
    m_RectangleShape.setSize(size);
    setTextureIndex(textureIndex);
}

sf::Vector2f Platformer::SpriteObject::getSize() const {
    return m_RectangleShape.getSize();
}

void Platformer::SpriteObject::setTextureIndex(const sf::Vector2i& textureIndex) {
    sf::IntRect textureRect(textureIndex, sf::Vector2i(getSize()));
    textureRect.position.x *= textureRect.size.x;
    textureRect.position.y *= textureRect.size.y;
    m_RectangleShape.setTextureRect(textureRect);
}

sf::Vector2i Platformer::SpriteObject::getTextureIndex() const {
    sf::IntRect textureRect = m_RectangleShape.getTextureRect();
    textureRect.position.x /= textureRect.size.x;
    textureRect.position.y /= textureRect.size.y;
    return textureRect.position;
}
