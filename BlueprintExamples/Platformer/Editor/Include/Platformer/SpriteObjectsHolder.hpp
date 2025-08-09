#ifndef PLATFORMER_EDITOR_SPRITE_OBJECTS_HOLDER_HPP
#define PLATFORMER_EDITOR_SPRITE_OBJECTS_HOLDER_HPP

#include "Platformer/SpriteObject.hpp"
#include "nlohmann/json.hpp"

namespace Platformer {
class SpriteObjectsHolder {
public:
    ~SpriteObjectsHolder();

public:
    void setTextureResource(const Blueprint::Resources::TextureResource& textureResource);

    void load(const nlohmann::ordered_json& data);

    void save(nlohmann::ordered_json& data);

    void updateAdd(const sf::Vector2f& mousePosition);

    void updateRemove(const sf::Vector2f& mousePosition);

    void render(sf::RenderTarget& renderTarget);

private:
    Blueprint::Resources::TextureResource m_Resource;
    std::vector<SpriteObject*>            m_SpriteObjects;
};
} // Platformer

#endif // PLATFORMER_EDITOR_SPRITE_OBJECTS_HOLDER_HPP
