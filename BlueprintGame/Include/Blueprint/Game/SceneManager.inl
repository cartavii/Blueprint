#ifndef BLUEPRINT_GAME_SCENE_MANAGER_INL
#define BLUEPRINT_GAME_SCENE_MANAGER_INL

#include "Blueprint/Game/SceneManager.hpp"

template<class TScene>
void Blueprint::Game::SceneManager::registerScene(const std::string& typeName) {
    if (m_Create.find(typeName) != m_Create.end()) {
        throw SceneAlreadyRegisteredException(typeName);
    }
    m_Create[typeName] = [](SceneManager& sceneManager)->Scene* { return new TScene(sceneManager); };
}

#endif // BLUEPRINT_GAME_SCENE_MANAGER_INL
