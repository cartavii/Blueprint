#ifndef BLUEPRINT_GAME_SCENE_MANAGER_HPP
#define BLUEPRINT_GAME_SCENE_MANAGER_HPP

#include <filesystem>
#include <queue>
#include <unordered_map>
#include <SFML/System/Clock.hpp>

#include "Blueprint/Core/Exception.hpp"
#include "Blueprint/Game/Scene.hpp"
#include "Blueprint/Resources/ResourceManager.hpp"

namespace Blueprint::Game {
class Application;
class Scene;
class SceneFabric;

class SceneInvalidPathException final : public Core::Exception {
public:
    explicit SceneInvalidPathException(const std::string& path);
};

class SceneFileExtensionException final : public Core::Exception {
public:
    explicit SceneFileExtensionException(const std::string& fileType);
};

class FailedToParseSceneDataException final : public Core::Exception {
public:
    explicit FailedToParseSceneDataException(const std::string& path);
};

class SceneDataTypeMissingException final : public Core::Exception {
public:
    explicit SceneDataTypeMissingException(const std::string& path);
};

class SceneNotFoundException final : public Core::Exception {
public:
    explicit SceneNotFoundException(const std::string& path);
};

class SceneManager : private Resources::ResourceManager {
public:
    explicit SceneManager(Application& application);
    ~SceneManager();

public:
    void update();
    void render();
    bool isRunning() const;

    Application& getApplication();
    const Application& getApplication() const;

    void loadScene(const std::filesystem::path& path);
    void unloadScene(const std::filesystem::path& path);

    void setCurrentScene(const std::filesystem::path& path);
    [[nodiscard]] bool isSceneLoaded(const std::filesystem::path& path) const;
    [[nodiscard]] bool isSceneCurrent(const std::filesystem::path& path) const;

private:
    nlohmann::ordered_json loadData(const std::filesystem::path& path);
    void saveData(const nlohmann::json& data, const std::filesystem::path& path);
    std::string getSceneType(const std::filesystem::path& path);
    void updateCurrentScene();
    void loadScenes();
    void loadScene(const std::filesystem::path& path, Scene* scene);
    void unloadScenes();

private:
    Application& m_Application;
    SceneFabric& m_Fabric;
    sf::Clock m_DeltaClock;
    Scene* m_CurrentScene;
    Scene* m_NextCurrentScene;
    std::unordered_map<std::filesystem::path, Scene*> m_Scenes;
    std::queue<std::pair<std::filesystem::path, Scene*>> m_LoadQueue;
    std::queue<std::pair<std::filesystem::path, Scene*>> m_UnloadQueue;
};
} // Blueprint::Editor

#endif // BLUEPRINT_GAME_SCENE_MANAGER_HPP
