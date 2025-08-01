#include "Blueprint/Game/SceneManager.hpp"
#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/Scene.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

Blueprint::Game::SceneAlreadyRegisteredException::SceneAlreadyRegisteredException(const std::string& typeName)
: Exception("Scene '" + typeName + "' is already registered") {}

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

Blueprint::Game::SceneUnsupportedType::SceneUnsupportedType(const std::string& sceneType)
: Exception("Scene type '" + sceneType + "' is not registered") {}

Blueprint::Game::SceneManager::SceneManager(Application& application)
: ResourceManager(Resources::SubFolder{"Scenes"})
, m_Application(application)
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
    if (m_CurrentScene != nullptr) {
        m_CurrentScene->update(m_DeltaClock.restart());
        updateCurrentScene();
        loadScenes();
        unloadScenes();
    }
}

void Blueprint::Game::SceneManager::render() {
    if (m_CurrentScene != nullptr) {
        m_CurrentScene->render(m_Application.getRenderWindow());
    }
}

bool Blueprint::Game::SceneManager::isRunning() const {
    return m_CurrentScene != nullptr;
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
    if (m_Create.find(sceneType) == m_Create.end()) {
        throw SceneUnsupportedType(sceneType);
    }
    Scene* scene = m_Create.at(sceneType)(*this);
    if (m_CurrentScene != nullptr) {
        m_LoadQueue.push({path, scene});
    } else {
        loadScene(path, scene);
    }
}

void Blueprint::Game::SceneManager::unloadScene(const std::filesystem::path& path) {
    const auto it = m_Scenes.find(path);
    if (it == m_Scenes.end()) {
        throw SceneNotFoundException(path.string());
    }
    m_UnloadQueue.push({it->first, it->second});
    m_Scenes.erase(it);
}

void Blueprint::Game::SceneManager::setCurrentScene(const std::filesystem::path& path) {
    Scene* nextCurrentScene = nullptr;
    const auto it = m_Scenes.find(path);
    if (it == m_Scenes.end()) {
        throw SceneNotFoundException(path.string());
    }
    nextCurrentScene = it->second;
    if (m_CurrentScene == nullptr) {
        m_CurrentScene = nextCurrentScene;
    } else {
        m_NextCurrentScene = nextCurrentScene;
    }
}

bool Blueprint::Game::SceneManager::isSceneLoaded(const std::filesystem::path& path) const {
    return m_Scenes.find(path) != m_Scenes.end();
}

bool Blueprint::Game::SceneManager::isSceneCurrent(const std::filesystem::path& path) const {
    if (m_CurrentScene == nullptr) {
        return false;
    }
    const auto it = m_Scenes.find(path);
    if (it == m_Scenes.end()) {
        throw SceneNotFoundException(path.string());
    }
    return it->second == m_CurrentScene;
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
    while (!m_LoadQueue.empty()) {
        auto [path, scene] = m_LoadQueue.front();
        m_LoadQueue.pop();
        loadScene(path, scene);
    }
}

void Blueprint::Game::SceneManager::loadScene(const std::filesystem::path& path, Scene* scene) {
    m_Scenes[path] = scene;
    scene->load(loadData(path));
}

void Blueprint::Game::SceneManager::unloadScenes() {
    while (!m_UnloadQueue.empty()) {
        auto [path, scene] = m_UnloadQueue.front();
        m_UnloadQueue.pop();
        nlohmann::ordered_json data;
        data["Type"] = getSceneType(path); // rework later
        scene->save(data);
        saveData(data, path);
        delete scene;
    }
}
