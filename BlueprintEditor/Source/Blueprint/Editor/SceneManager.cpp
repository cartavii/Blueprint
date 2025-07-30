#include "Blueprint/Editor/SceneManager.hpp"
#include "Blueprint/Editor/Application.hpp"
#include "Blueprint/Editor/SceneEditor.hpp"

#include <fstream>

Blueprint::Editor::SceneTypeMissing::SceneTypeMissing(const std::filesystem::path& path)
: Exception("Missing 'Type' field inside file '" + path.string() + "'") {}

Blueprint::Editor::SceneAlreadyLoaded::SceneAlreadyLoaded(const std::filesystem::path& path)
: Exception("Scene with path '" + path.string() + "' is already loaded") {}

Blueprint::Editor::SceneIsNotLoaded::SceneIsNotLoaded(const std::filesystem::path& path)
: Exception("Failed to find scene with path '" + path.string() + "'") {}

Blueprint::Editor::SceneManager::SceneManager(Application& application)
: ResourceManager("Scenes")
, m_Application(application)
, m_SceneFabric(application.getSceneFabric()) {}

Blueprint::Editor::SceneManager::~SceneManager() {
    clear();
}

void Blueprint::Editor::SceneManager::loadSceneEditor(const std::filesystem::path& path) {
    for (const auto [sceneEditor, keyName, otherPath] : m_SceneHolders) {
        if (otherPath == path) {
            throw SceneAlreadyLoaded(path);
        }
    }
    if (!isPathValid(path)) {
        throw Resources::FailedToOpenFileException(path.string());
    }
    nlohmann::json sceneData = loadSceneData(getFullPath(path));
    if (!sceneData.contains("Type")) {
        throw SceneTypeMissing(path);
    }
    const std::string sceneType = sceneData["Type"].get<std::string>();
    SceneEditor* sceneEditor = m_SceneFabric.createSceneEditor(sceneType);
    sceneEditor->load(sceneData);
    m_SceneHolders.push_back({sceneEditor, sceneType, path});
}

void Blueprint::Editor::SceneManager::unloadSceneEditor(const std::filesystem::path& path) {
    for (auto it = begin(); it != end(); ++it) {
        if (auto [sceneEditor, keyName, otherPath] = *it; otherPath == path) {
            const std::filesystem::path fullPath = getFullPath(path);
            nlohmann::json sceneData = loadSceneData(fullPath);
            if (!sceneData.contains("Type")) {
                sceneData["Type"] = keyName;
            }
            sceneEditor->save(sceneData);
            saveSceneData(fullPath, sceneData);
            delete sceneEditor;
            m_SceneHolders.erase(it);
            return;
        }
    }
}

void Blueprint::Editor::SceneManager::clear() {
    for (const auto [sceneEditor, keyName, path] : m_SceneHolders) {
        const std::filesystem::path fullPath = getFullPath(path);
        nlohmann::json sceneData;
        sceneData["Type"] = keyName;
        sceneEditor->save(sceneData);
        saveSceneData(fullPath, sceneData);
        delete sceneEditor;
    }
    m_SceneHolders.clear();
}

Blueprint::Editor::Application& Blueprint::Editor::SceneManager::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::SceneManager::getApplication() const {
    return m_Application;
}

std::size_t Blueprint::Editor::SceneManager::getSceneHolderCount() const {
    return m_SceneHolders.size();
}

Blueprint::Editor::SceneManager::iterator Blueprint::Editor::SceneManager::begin() {
    return m_SceneHolders.begin();
}

Blueprint::Editor::SceneManager::iterator Blueprint::Editor::SceneManager::end() {
    return m_SceneHolders.end();
}

Blueprint::Editor::SceneManager::constIterator Blueprint::Editor::SceneManager::begin() const {
    return m_SceneHolders.begin();
}

Blueprint::Editor::SceneManager::constIterator Blueprint::Editor::SceneManager::end() const {
    return m_SceneHolders.end();
}

nlohmann::json Blueprint::Editor::SceneManager::loadSceneData(const std::filesystem::path& path) {
    std::ifstream file(path);
    nlohmann::json sceneData;
    if (file.is_open()) {
        file >> sceneData;
        file.close();
    }
    return sceneData;
}

void Blueprint::Editor::SceneManager::saveSceneData(const std::filesystem::path& path, const nlohmann::json& sceneData) {
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    file << std::setw(4) << sceneData;
    file.close();
}
