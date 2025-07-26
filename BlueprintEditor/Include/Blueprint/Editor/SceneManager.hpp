#ifndef BLUEPRINT_EDITOR_SCENE_MANAGER_HPP
#define BLUEPRINT_EDITOR_SCENE_MANAGER_HPP

#include "Blueprint/Core/Exception.hpp"
#include "Blueprint/Resources/ResourceManager.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace Blueprint::Editor {
class Application;
class SceneEditor;
class SceneFabric;

class SceneTypeMissing final : public Core::Exception {
public:
    explicit SceneTypeMissing(const std::filesystem::path& path);
};

class SceneAlreadyLoaded final : public Core::Exception {
public:
    explicit SceneAlreadyLoaded(const std::filesystem::path& path);
};

class SceneIsNotLoaded final : public Core::Exception {
public:
    explicit SceneIsNotLoaded(const std::filesystem::path& path);
};

class SceneManager : private Resources::ResourceManager {
public:
    struct SceneHolder {
        SceneEditor* sceneEditor;
        std::string keyName;
        std::filesystem::path path;
    };
    using iterator = std::vector<SceneHolder>::iterator;
    using constIterator = std::vector<SceneHolder>::const_iterator;

public:
    explicit SceneManager(Application& application);
    ~SceneManager();

public:
    void loadSceneEditor(const std::filesystem::path& path);
    void unloadSceneEditor(const std::filesystem::path& path);
    void clear();

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

    [[nodiscard]] std::size_t getSceneHolderCount() const;

    iterator begin();
    iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    nlohmann::json loadSceneData(const std::filesystem::path& path);
    void saveSceneData(const std::filesystem::path& path, const nlohmann::json& sceneData);

private:
    Application& m_Application;
    SceneFabric& m_SceneFabric;
    std::vector<SceneHolder> m_SceneHolders;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_MANAGER_HPP
