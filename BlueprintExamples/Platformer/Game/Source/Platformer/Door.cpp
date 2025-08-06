#include "Platformer/Door.hpp"
#include "Platformer/Loader.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Platformer::Door::Door() : m_RectangleShape(sf::Vector2f(16.f, 16.f)) {
    setTileIndex(sf::Vector2i());
}

void Platformer::Door::load(const nlohmann::ordered_json& data) {
    if (data.contains("Position")) {
        setPosition(Loader::loadVector2f(data["Position"]));
    }
}

void Platformer::Door::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_RectangleShape);
}

void Platformer::Door::setPosition(const sf::Vector2f& position) {
    m_RectangleShape.setPosition(position);
}

sf::Vector2f Platformer::Door::getPosition() const {
    return m_RectangleShape.getPosition();
}

void Platformer::Door::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_Resource = textureResource;
    m_RectangleShape.setTexture(m_Resource.getTexture());
}

void Platformer::Door::setTileIndex(const sf::Vector2i& tilePosition) {
    m_RectangleShape.setTextureRect(sf::IntRect(tilePosition * 16, sf::Vector2i(16, 16)));
}

sf::FloatRect Platformer::Door::getBoundingBox() const {
    return m_RectangleShape.getGlobalBounds();
}
