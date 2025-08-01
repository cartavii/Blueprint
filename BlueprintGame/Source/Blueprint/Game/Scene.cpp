#include "Blueprint/Game/Scene.hpp"

Blueprint::Game::Scene::Scene(SceneManager& manager) : m_Manager(manager) {}

Blueprint::Game::SceneManager& Blueprint::Game::Scene::getSceneManager() {
    return m_Manager;
}

const Blueprint::Game::SceneManager& Blueprint::Game::Scene::getSceneManager() const {
    return m_Manager;
}
