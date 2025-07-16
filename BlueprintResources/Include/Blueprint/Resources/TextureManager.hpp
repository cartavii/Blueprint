#ifndef BLUEPRINT_RESOURCES_TEXTURE_MANAGER_HPP
#define BLUEPRINT_RESOURCES_TEXTURE_MANAGER_HPP

#include "Blueprint/Resources/ResourceManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <unordered_map>

namespace Blueprint::Resources {
class FailedToLoadTextureException final : public Core::Exception {
public:
    explicit FailedToLoadTextureException(const std::string& path);
};

class TextureNotFoundException final : public Core::Exception {
public:
    TextureNotFoundException();
};

class TextureManager : private ResourceManager {
public:
    TextureManager();
    ~TextureManager();

public:
    const sf::Texture* loadTexture(const std::filesystem::path& path);
    void unloadTexture(const sf::Texture* texture);

private:
    struct TextureHolder {
        sf::Texture* texture;
        std::uint16_t count;
    };

private:
    std::unordered_map<std::filesystem::path, TextureHolder> m_Textures;
};
} // Blueprint::Resources

#endif // BLUEPRINT_RESOURCES_TEXTURE_MANAGER_HPP
