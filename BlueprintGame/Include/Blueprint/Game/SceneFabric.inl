#ifndef BLUEPRINT_GAME_SCENE_FABRIC_INL
#define BLUEPRINT_GAME_SCENE_FABRIC_INL

#include "Blueprint/Game/SceneFabric.hpp"

template<class TScene>
void Blueprint::Game::SceneFabric::registerScene(const std::string& keyName) {
    m_Creates[keyName] = [](SceneManager& sceneManager) -> Scene* {
        Scene* sceneEditor = new TScene(sceneManager);
        return sceneEditor;
    };
}

#endif // BLUEPRINT_GAME_SCENE_FABRIC_INL
