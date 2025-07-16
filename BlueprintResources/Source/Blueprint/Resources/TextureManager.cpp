#include "Blueprint/Resources/TextureManager.hpp"

#include <SFML/Graphics/Text.hpp>

Blueprint::Resources::FailedToLoadTextureException::FailedToLoadTextureException(const std::string& path)
: Exception("Failed to load texture\n Path'" + path + "'") {}

Blueprint::Resources::TextureNotFoundException::TextureNotFoundException()
: Exception("Failed to find texture by reference") {}

Blueprint::Resources::TextureManager::TextureManager() : ResourceManager("Textures") {}

Blueprint::Resources::TextureManager::~TextureManager() {
    for (auto [path, textureHolder] : m_Textures) {
        delete textureHolder.texture;
    }
}

const sf::Texture* Blueprint::Resources::TextureManager::loadTexture(const std::filesystem::path& path) {
    if (!isPathValid(path)) {
        throw FailedToOpenFileException(path.string());
    }
    if (const auto it = m_Textures.find(path); it != m_Textures.end()) {
        return it->second.texture;
    }
    auto* texture = new sf::Texture;
    if (const std::filesystem::path fullPath = getFullPath(path); !texture->loadFromFile(fullPath)) {
        delete texture;
        throw FailedToOpenFileException(fullPath.string());
    }
    constexpr std::uint16_t textureCount = 1;
    m_Textures[path] = TextureHolder{texture, textureCount};
    return texture;
}

void Blueprint::Resources::TextureManager::unloadTexture(const sf::Texture* texture) {
    for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it) {
        if (it->second.texture == texture) {
            if (--it->second.count == 0) {
                delete texture;
                m_Textures.erase(it);
            }
            return;
        }
    }
    throw TextureNotFoundException();
}
