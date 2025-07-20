#include "Blueprint/Resources/TextureManager.hpp"

#include <SFML/Graphics/Text.hpp>

Blueprint::Resources::FailedToLoadTextureException::FailedToLoadTextureException(const std::string& path)
: Exception("Failed to load texture\n Path'" + path + "'") {}

Blueprint::Resources::TextureNotFoundException::TextureNotFoundException()
: Exception("Failed to find texture by reference") {}

Blueprint::Resources::TextureResource::TextureResource()
: m_Manager(nullptr)
, m_Texture(nullptr) {}

Blueprint::Resources::TextureResource::TextureResource(TextureManager* manager, std::filesystem::path path, const sf::Texture* texture)
: m_Manager(manager)
, m_Path(std::move(path))
, m_Texture(texture) {
    increase();
}

Blueprint::Resources::TextureResource::TextureResource(const TextureResource& other)
: m_Manager(other.m_Manager)
, m_Path(other.m_Path)
, m_Texture(other.m_Texture) {
    increase();
}

Blueprint::Resources::TextureResource::~TextureResource() {
    decrease();
}

const sf::Texture* Blueprint::Resources::TextureResource::getTexture() const {
    return m_Texture;
}

Blueprint::Resources::TextureResource& Blueprint::Resources::TextureResource::operator=(const TextureResource& other) {
    if (*this == other) {
        return *this;
    }
    decrease();
    m_Manager = other.m_Manager;
    m_Path = other.m_Path;
    m_Texture = other.m_Texture;
    increase();
    return *this;
}

bool Blueprint::Resources::TextureResource::operator==(const TextureResource& other) const {
    return this == &other
        && m_Manager == other.m_Manager
        && m_Path == other.m_Path
        && m_Texture == other.m_Texture;
}

void Blueprint::Resources::TextureResource::increase() {
    if (m_Manager == nullptr || m_Texture == nullptr) {
        return;
    }
    ++m_Manager->m_Textures.at(m_Path).count;
}

void Blueprint::Resources::TextureResource::decrease() {
    if (m_Manager == nullptr || m_Texture == nullptr) {
        return;
    }
    if (--m_Manager->m_Textures.at(m_Path).count == 0) {
        delete m_Texture;
        m_Manager->m_Textures.erase(m_Path);
    }
}

Blueprint::Resources::TextureManager::TextureManager() : ResourceManager("Textures") {}

Blueprint::Resources::TextureManager::~TextureManager() {
    for (const auto& [path, textureHolder] : m_Textures) {
        delete textureHolder.texture;
    }
}

Blueprint::Resources::TextureResource Blueprint::Resources::TextureManager::getTextureResource(const std::filesystem::path& texturePath) {
    if (!isPathValid(texturePath)) {
        throw TextureNotFoundException();
    }
    const std::filesystem::path fullPath = getFullPath(texturePath);
    if (const auto it = m_Textures.find(fullPath); it != m_Textures.end()) {
        return TextureResource(this, fullPath, it->second.texture);
    }
    sf::Texture* texture = new sf::Texture;
    if (!texture->loadFromFile(fullPath)) {
        delete texture;
        throw TextureNotFoundException();
    }
    m_Textures[fullPath] = {texture, 0};
    return TextureResource(this, fullPath, texture);
}
