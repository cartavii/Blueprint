#include "Platformer/TilesHolder.hpp"
#include "Platformer/Loader.hpp"
#include "Platformer/Saver.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Platformer::TilesHolder::TilesHolder() : m_TileRectangle(sf::Vector2f(16.f, 16.f)) {}

void Platformer::TilesHolder::load(const nlohmann::ordered_json& tilesData) {
    for (const nlohmann::ordered_json& tileData : tilesData) {
        loadTile(tileData);
    }
}

void Platformer::TilesHolder::save(nlohmann::ordered_json& tilesData) {
    for (const Tile& tile : m_Tiles) {
        nlohmann::ordered_json tileData;
        saveTile(tileData, tile);
        tilesData.push_back(tileData);
    }
}

void Platformer::TilesHolder::render(sf::RenderTarget& renderTarget) {
    for (const Tile& tile : m_Tiles) {
        sf::Vector2<bool> expand;
        expand.x = tile.bottomRight.x - tile.topLeft.x > 16.f;
        expand.y = tile.bottomRight.y - tile.topLeft.y > 16.f;
        if (expand.x && expand.y) {
            renderTileNxM(renderTarget, tile);
        } else if (expand.x) {
            renderTileNx1(renderTarget, tile);
        } else if (expand.y) {
            renderTile1xN(renderTarget, tile);
        } else {
            renderTile1x1(renderTarget, tile);
        }
    }
}

void Platformer::TilesHolder::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_TextureResource = textureResource;
    m_TileRectangle.setTexture(m_TextureResource.getTexture());
}

const Blueprint::Resources::TextureResource& Platformer::TilesHolder::getTextureResource() const {
    return m_TextureResource;
}

Platformer::TilesHolder::Tile& Platformer::TilesHolder::addTile(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight) {
    m_Tiles.push_back({topLeft, bottomRight});
    return m_Tiles.back();
}

Platformer::TilesHolder::iterator Platformer::TilesHolder::removeTile(const constIterator tileIterator) {
    return m_Tiles.erase(tileIterator);
}

std::size_t Platformer::TilesHolder::getTileCount() const {
    return m_Tiles.size();
}

Platformer::TilesHolder::iterator Platformer::TilesHolder::findTile(const sf::Vector2f& position) {
    iterator it = m_Tiles.begin();
    for (; it != m_Tiles.end(); ++it) {
        if (position.x >= it->topLeft.x && position.y >= it->topLeft.y &&
            position.x >= it->bottomRight.x && position.y >= it->bottomRight.y) {
            return it;
        }
    }
    return it;
}

Platformer::TilesHolder::constIterator Platformer::TilesHolder::findTile(const sf::Vector2f& position) const {
    constIterator it = m_Tiles.begin();
    for (; it != m_Tiles.end(); ++it) {
        if (position.x >= it->topLeft.x && position.y >= it->topLeft.y &&
            position.x >= it->bottomRight.x && position.y >= it->bottomRight.y) {
            return it;
        }
    }
    return it;
}

Platformer::TilesHolder::iterator Platformer::TilesHolder::begin() {
    return m_Tiles.begin();
}

Platformer::TilesHolder::iterator Platformer::TilesHolder::end() {
    return m_Tiles.end();
}

Platformer::TilesHolder::constIterator Platformer::TilesHolder::begin() const {
    return m_Tiles.begin();
}

Platformer::TilesHolder::constIterator Platformer::TilesHolder::end() const {
    return m_Tiles.end();
}

void Platformer::TilesHolder::loadTile(const nlohmann::ordered_json& tileData) {
    const sf::Vector2f topLeft = Loader::loadVector2f(tileData, "TopLeft");
    const sf::Vector2f bottomRight = Loader::loadVector2f(tileData, "BottomRight");
    addTile(topLeft, bottomRight);
}

void Platformer::TilesHolder::saveTile(nlohmann::ordered_json& tileData, const Tile& tile) {
    Saver::saveVector2f(tileData, tile.topLeft, "TopLeft");
    Saver::saveVector2f(tileData, tile.bottomRight, "BottomRight");
}

void Platformer::TilesHolder::setTileIndex(const sf::Vector2i& tileIndex) {
    m_TileRectangle.setTextureRect(sf::IntRect(tileIndex * 16, sf::Vector2i(16, 16)));
}

void Platformer::TilesHolder::renderTileNxM(sf::RenderTarget& renderTarget, const Tile& tile) {
    sf::Vector2f position = tile.topLeft;
    setTileIndex(sf::Vector2i(0, 0));
    m_TileRectangle.setPosition(position);
    renderTarget.draw(m_TileRectangle);

    position = sf::Vector2f(tile.bottomRight.x - 16.f, tile.topLeft.y);
    setTileIndex(sf::Vector2i(2, 0));
    m_TileRectangle.setPosition(position);
    renderTarget.draw(m_TileRectangle);

    position = sf::Vector2f(tile.topLeft.x, tile.bottomRight.y - 16.f);
    setTileIndex(sf::Vector2i(0, 2));
    m_TileRectangle.setPosition(position);
    renderTarget.draw(m_TileRectangle);

    position = tile.bottomRight - sf::Vector2f(16.f, 16.f);
    setTileIndex(sf::Vector2i(2, 2));
    m_TileRectangle.setPosition(position);
    renderTarget.draw(m_TileRectangle);

    position = tile.topLeft;
    setTileIndex(sf::Vector2i(1, 0));
    for (position.x += 16.f; position.x < tile.bottomRight.x - 16.f; position.x += 16.f) {
        m_TileRectangle.setPosition(position);
        renderTarget.draw(m_TileRectangle);
    }
    position = sf::Vector2f(tile.topLeft.x + 16.f, tile.bottomRight.y - 16.f);
    setTileIndex(sf::Vector2i(1, 2));
    for (; position.x < tile.bottomRight.x - 16.f; position.x += 16.f) {
        m_TileRectangle.setPosition(position);
        renderTarget.draw(m_TileRectangle);
    }
    position = tile.topLeft;
    setTileIndex(sf::Vector2i(0, 1));
    for (position.y += 16.f; position.y < tile.bottomRight.y- 16.f; position.y += 16.f) {
        m_TileRectangle.setPosition(position);
        renderTarget.draw(m_TileRectangle);
    }
    position = sf::Vector2f(tile.bottomRight.x - 16.f, tile.topLeft.y + 16.f);
    setTileIndex(sf::Vector2i(2, 1));
    for (; position.y < tile.bottomRight.y - 16.f; position.y += 16.f) {
        m_TileRectangle.setPosition(position);
        renderTarget.draw(m_TileRectangle);
    }
    setTileIndex(sf::Vector2i(1, 1));
    for (position.y = tile.topLeft.y + 16.f; position.y < tile.bottomRight.y - 16.f; position.y += 16.f) {
        for (position.x = tile.topLeft.x + 16.f; position.x < tile.bottomRight.x - 16.f; position.x += 16.f) {
            m_TileRectangle.setPosition(position);
            renderTarget.draw(m_TileRectangle);
        }
    }
}

void Platformer::TilesHolder::renderTileNx1(sf::RenderTarget& renderTarget, const Tile& tile) {
    sf::Vector2f topLeft = tile.topLeft;

    setTileIndex(sf::Vector2i(0, 3));
    m_TileRectangle.setPosition(topLeft);
    renderTarget.draw(m_TileRectangle);

    setTileIndex(sf::Vector2i(1, 3));
    topLeft.x += 16.f;
    for (; topLeft.x < tile.bottomRight.x - 16.f; topLeft.x += 16.f) {
        m_TileRectangle.setPosition(topLeft);
        renderTarget.draw(m_TileRectangle);
    }

    setTileIndex(sf::Vector2i(2, 3));
    m_TileRectangle.setPosition(topLeft);
    renderTarget.draw(m_TileRectangle);
}

void Platformer::TilesHolder::renderTile1xN(sf::RenderTarget& renderTarget, const Tile& tile) {
    sf::Vector2f topLeft = tile.topLeft;

    setTileIndex(sf::Vector2i(3, 0));
    m_TileRectangle.setPosition(topLeft);
    renderTarget.draw(m_TileRectangle);

    setTileIndex(sf::Vector2i(3, 1));
    topLeft.y += 16.f;
    for (; topLeft.y < tile.bottomRight.y - 16.f; topLeft.y += 16.f) {
        m_TileRectangle.setPosition(topLeft);
        renderTarget.draw(m_TileRectangle);
    }

    setTileIndex(sf::Vector2i(3, 2));
    m_TileRectangle.setPosition(topLeft);
    renderTarget.draw(m_TileRectangle);
}

void Platformer::TilesHolder::renderTile1x1(sf::RenderTarget& renderTarget, const Tile& tile) {
    setTileIndex(sf::Vector2i(3, 3));
    m_TileRectangle.setPosition(tile.topLeft);
    renderTarget.draw(m_TileRectangle);
}
