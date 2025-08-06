#include "Blueprint/Game/SceneManager.hpp"
#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/Scene.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

Blueprint::Game::SceneInvalidPathException::SceneInvalidPathException(const std::string& path)
: Exception("Invalid scene path: '" + path + "'") {}

Blueprint::Game::SceneFileExtensionException::SceneFileExtensionException(const std::string& fileType)
: Exception("Scene file extension must be 'bpscene', not '" + fileType + "'") {}

Blueprint::Game::FailedToParseSceneDataException::FailedToParseSceneDataException(const std::string& path)
: Exception("Failed to interpret scene data as json file\n Path: '" + path + "'") {}

Blueprint::Game::SceneDataTypeMissingException::SceneDataTypeMissingException(const std::string& path)
: Exception("Scene file missing field: 'Type'\n Path: '" + path + "'") {}

Blueprint::Game::SceneNotFoundException::SceneNotFoundException(const std::string& path)
: Exception("Failed to find scene with path '" + path + "'") {}

Blueprint::Game::SceneManager::SceneManager(Application& application)
: ResourceManager(Resources::SubFolder{"Scenes"})
, m_Application(application)
, m_Fabric(application.getSceneFabric())
, m_CurrentScene(nullptr)
, m_NextCurrentScene(nullptr) {}

Blueprint::Game::SceneManager::~SceneManager() {
    loadScenes();
    for (auto [path, scene] : m_Scenes) {
        delete scene;
    }
    unloadScenes();
}

void Blueprint::Game::SceneManager::update() {
    updateCurrentScene();
    loadScenes();
    unloadScenes();
    if (m_CurrentScene != nullptr) {
        m_CurrentScene->update(m_DeltaClock.restart());
    }
}

void Blueprint::Game::SceneManager::render() {
    if (m_CurrentScene != nullptr) {
        m_CurrentScene->render(m_Application.getRenderWindow());
    }
}

bool Blueprint::Game::SceneManager::isRunning() const {
    return m_CurrentScene != nullptr || m_NextCurrentScene != nullptr;
}

Blueprint::Game::Application& Blueprint::Game::SceneManager::getApplication() {
    return m_Application;
}

const Blueprint::Game::Application& Blueprint::Game::SceneManager::getApplication() const {
    return m_Application;
}

void Blueprint::Game::SceneManager::loadScene(const std::filesystem::path& path) {
    if (!isPathValid(path)) {
        throw SceneInvalidPathException(path.string());
    }
    if (const std::filesystem::path extension = path.extension(); extension.string() != ".scenebp") {
        throw SceneFileExtensionException(extension.string());
    }
    const std::string sceneType = getSceneType(path);
    Scene* scene = m_Fabric.createScene(sceneType);
    m_LoadQueue.push_back({path, scene});
}

void Blueprint::Game::SceneManager::unloadScene(const std::filesystem::path& path) {
    Scene* scene = find(path);
    if (scene == nullptr) {
        throw SceneNotFoundException(path.string());
    }
    m_UnloadQueue.push_back({path, scene});
    remove(path);
}

void Blueprint::Game::SceneManager::unloadScene(Scene& scene) {
    if (const std::filesystem::path path = find(scene); !path.empty()) {
        m_UnloadQueue.push_back({path, &scene});
        remove(path);
    }
}

void Blueprint::Game::SceneManager::reloadScene(const std::filesystem::path& path) {
    Scene* scene = find(path);
    if (scene == nullptr) {
        throw SceneNotFoundException(path.string());
    }
    unloadScene(path, *scene);
    loadScene(path, *scene);
}

void Blueprint::Game::SceneManager::reloadScene(Scene& scene) {
    if (const std::filesystem::path path = find(scene); !path.empty()) {
        unloadScene(path, scene);
        loadScene(path, scene);
    }
}

void Blueprint::Game::SceneManager::setCurrentScene(const std::filesystem::path& path) {
    if (Scene* scene = find(path); scene != nullptr) {
        m_NextCurrentScene = scene;
        return;
    }
    for (auto it = m_LoadQueue.begin(); it != m_LoadQueue.end(); ++it) {
        if (it->first == path) {
            m_NextCurrentScene = it->second;
            return;
        }
    }
    throw SceneNotFoundException(path.string());
}

void Blueprint::Game::SceneManager::setCurrentScene(Scene& scene) {
    for (const auto& [path, otherScene] : m_UnloadQueue) {
        if (otherScene == &scene) {
            return;
        }
    }
    m_NextCurrentScene = &scene;
}

void Blueprint::Game::SceneManager::resetCurrentScene() {
    m_NextCurrentScene = nullptr;
}

std::filesystem::path Blueprint::Game::SceneManager::getFrontScene() const {
    if (m_Scenes.empty()) {
        if (!m_LoadQueue.empty()) {
            return m_LoadQueue.front().first;
        }
        return {};
    }
    return m_Scenes.front().first;
}

std::filesystem::path Blueprint::Game::SceneManager::getBackScene() const {
    if (!m_LoadQueue.empty()) {
        return m_LoadQueue.back().first;
    }
    if (m_Scenes.empty()) {
        return {};
    }
    return m_Scenes.back().first;
}

void Blueprint::Game::SceneManager::addScene(const std::filesystem::path& path, Scene* scene) {
    m_Scenes.push_back({path, scene});
}

void Blueprint::Game::SceneManager::removeScene(const std::filesystem::path& path) {
    for (auto it = m_Scenes.begin(); it != m_Scenes.end(); ++it) {
        if (it->first == path) {
            m_Scenes.erase(it);
            return;
        }
    }
}

Blueprint::Game::Scene* Blueprint::Game::SceneManager::find(const std::filesystem::path& path) const {
    for (const auto& [otherPath, scene] : m_Scenes) {
        if (path == otherPath) {
            return scene;
        }
    }
    return nullptr;
}

std::filesystem::path Blueprint::Game::SceneManager::find(const Scene& scene) const {
    for (const auto& [path, otherScene] : m_Scenes) {
        if (&scene == otherScene) {
            return path;
        }
    }
    return {};
}

nlohmann::ordered_json Blueprint::Game::SceneManager::loadData(const std::filesystem::path& path) {
    const std::filesystem::path fullPath = getFullPath(path);
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        throw Resources::FailedToOpenFileException(fullPath.string());
    }
    nlohmann::ordered_json data;
    if (!(file >> data)) {
        throw FailedToParseSceneDataException(fullPath.string());
    }
    file.close();
    return data;
}

void Blueprint::Game::SceneManager::saveData(const nlohmann::json& data, const std::filesystem::path& path) {
    const std::filesystem::path fullPath = getFullPath(path);
    std::ofstream file(fullPath);
    if (!file.is_open()) {
        throw Resources::FailedToOpenFileException(fullPath.string());
    }
    if (!(file << data)) {
        throw FailedToParseSceneDataException(fullPath.string());
    }
    file.close();
}

std::string Blueprint::Game::SceneManager::getSceneType(const std::filesystem::path& path) {
    nlohmann::json data = loadData(path);
    if (!data.contains("Type")) {
        throw SceneDataTypeMissingException(path.string());
    }
    return data.at("Type").get<std::string>();
}

void Blueprint::Game::SceneManager::updateCurrentScene() {
    if (m_NextCurrentScene != nullptr) {
        m_CurrentScene = m_NextCurrentScene;
        m_NextCurrentScene = nullptr;
    }
}

void Blueprint::Game::SceneManager::loadScenes() {
    for (auto [path, scene] : m_LoadQueue) {
        loadScene(path, *scene);
    }
    m_LoadQueue.clear();
}

void Blueprint::Game::SceneManager::loadScene(const std::filesystem::path& path, Scene& scene) {
    addScene(path, &scene);
    scene.load(loadData(path));
}

void Blueprint::Game::SceneManager::unloadScenes() {
    for (auto [path, scene] : m_UnloadQueue) {
        unloadScene(path, *scene);
        delete scene;
    }
    m_UnloadQueue.clear();
}

void Blueprint::Game::SceneManager::unloadScene(const std::filesystem::path& path, Scene& scene) {
    nlohmann::ordered_json data;
    data["Type"] = getSceneType(path);
    scene.save(data);
    saveData(data, path);
}
