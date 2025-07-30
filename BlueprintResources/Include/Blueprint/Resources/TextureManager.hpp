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

class TextureManager;

class TextureResource {
public:
    TextureResource();
    TextureResource(TextureManager* manager, std::filesystem::path path, const sf::Texture* texture);
    TextureResource(const TextureResource& other);
    ~TextureResource();

public:
    [[nodiscard]] const std::filesystem::path& getPath() const;
    [[nodiscard]] const sf::Texture* getTexture() const;

public:
    TextureResource& operator=(const TextureResource& other);
    [[nodiscard]] bool operator==(const TextureResource& other) const;

private:
    void increase();
    void decrease();

private:
    TextureManager* m_Manager;
    std::filesystem::path m_Path;
    const sf::Texture* m_Texture;
};

class TextureManager : private ResourceManager {
public:
    TextureManager();
    ~TextureManager();

public:
    TextureResource getTextureResource(const std::filesystem::path& texturePath);

private:
    struct TextureHolder {
        sf::Texture* texture;
        std::uint16_t count;
    };

private:
    std::unordered_map<std::filesystem::path, TextureHolder> m_Textures;
    friend TextureResource;
};
} // Blueprint::Resources

#endif // BLUEPRINT_RESOURCES_TEXTURE_MANAGER_HPP
