#include "Blueprint/Game/SceneFabric.hpp"
#include "Blueprint/Game/Application.hpp"

Blueprint::Game::SceneTypeNotRegistered::SceneTypeNotRegistered(const std::string& sceneType)
: Exception("Scene type '" + sceneType + "' is not registered") {}

Blueprint::Game::SceneFabric::SceneFabric(Application& application)
: m_Application(application)
, m_SceneManager(application.getSceneManager()) {}

Blueprint::Game::Scene* Blueprint::Game::SceneFabric::createScene(const std::string& keyName) {
    const auto it = m_Creates.find(keyName);
    if (it == m_Creates.end()) {
        throw SceneTypeNotRegistered(keyName);
    }
    return it->second(m_SceneManager);
}

Blueprint::Game::Application& Blueprint::Game::SceneFabric::getApplication() {
    return m_Application;
}

const Blueprint::Game::Application& Blueprint::Game::SceneFabric::getApplication() const {
    return m_Application;
}
