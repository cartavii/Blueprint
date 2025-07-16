#ifndef BLUEPRINT_RESOURCES_RESOURCE_MANAGER_HPP
#define BLUEPRINT_RESOURCES_RESOURCE_MANAGER_HPP

#include "Blueprint/Core/Exception.hpp"

#include <filesystem>

namespace Blueprint::Resources {
class FailedToOpenFileException final : public Core::Exception {
public:
    explicit FailedToOpenFileException(const std::string& path);
};

using SubFolder = std::filesystem::path;
class ResourceManager {
public:
    explicit ResourceManager(const std::filesystem::path& subFolder);

public:
    bool isPathValid(const std::filesystem::path& path) const;
    std::filesystem::path getFullPath(const std::filesystem::path& path) const;
    const std::filesystem::path& getRootPath() const;

private:
    const std::filesystem::path m_RootPath;
};
} // Blueprint::Resources

#endif // BLUEPRINT_RESOURCES_RESOURCE_MANAGER_HPP
