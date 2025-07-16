#include "Blueprint/Resources/ResourceManager.hpp"

Blueprint::Resources::FailedToOpenFileException::FailedToOpenFileException(const std::string& path)
: Exception("Failed to open file\n Path: '" + path + "'") {}

Blueprint::Resources::ResourceManager::ResourceManager(const std::filesystem::path& subFolder)
: m_RootPath("..\\Resources" / subFolder) {}

bool Blueprint::Resources::ResourceManager::isPathValid(const std::filesystem::path& path) const {
    if (path.is_absolute()) {
        return false;
    }
    for (const std::filesystem::path& part : path) {
        if (part == "..") {
            return false;
        }
    }
    return std::filesystem::exists(getFullPath(path));
}

std::filesystem::path Blueprint::Resources::ResourceManager::getFullPath(const std::filesystem::path& path) const {
    return m_RootPath / path;
}

const std::filesystem::path& Blueprint::Resources::ResourceManager::getRootPath() const {
    return m_RootPath;
}
