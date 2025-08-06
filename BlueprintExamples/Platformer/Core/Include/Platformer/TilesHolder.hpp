#ifndef PLATFORMER_EDITOR_TILES_HOLDER_HPP
#define PLATFORMER_EDITOR_TILES_HOLDER_HPP

#include "Blueprint/Resources/TextureManager.hpp"

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

namespace Platformer {
class TilesHolder {
public:
    struct Tile {
        sf::Vector2f topLeft;
        sf::Vector2f bottomRight;
    };
    using iterator = std::vector<Tile>::iterator;
    using constIterator = std::vector<Tile>::const_iterator;

public:
    TilesHolder();

public:
    void load(const nlohmann::ordered_json& tilesData);
    void save(nlohmann::ordered_json& tilesData);

    void render(sf::RenderTarget& renderTarget);

    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);
    [[nodiscard]] const Blueprint::Resources::TextureResource& getTextureResource() const;

    Tile& addTile(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight);
    iterator removeTile(constIterator tileIterator);

    [[nodiscard]] std::size_t getTileCount() const;

    iterator findTile(const sf::Vector2f& position);
    constIterator findTile(const sf::Vector2f& position) const;

    iterator begin();
    iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    void loadTile(const nlohmann::ordered_json& tileData);
    void saveTile(nlohmann::ordered_json& tileData, const Tile& tile);

    void setTileIndex(const sf::Vector2i& tileIndex);
    void renderTileNxM(sf::RenderTarget& renderTarget, const Tile& tile);
    void renderTileNx1(sf::RenderTarget& renderTarget, const Tile& tile);
    void renderTile1xN(sf::RenderTarget& renderTarget, const Tile& tile);
    void renderTile1x1(sf::RenderTarget& renderTarget, const Tile& tile);

private:
    Blueprint::Resources::TextureResource m_TextureResource;
    sf::RectangleShape m_TileRectangle;
    std::vector<Tile> m_Tiles;
};
} // Platformer

#endif // PLATFORMER_EDITOR_TILES_HOLDER_HPP
