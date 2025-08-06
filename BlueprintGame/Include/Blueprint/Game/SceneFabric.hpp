#ifndef BLUEPRINT_GAME_SCENE_FABRIC_HPP
#define BLUEPRINT_GAME_SCENE_FABRIC_HPP

#include "Blueprint/Core/Exception.hpp"
#include "Blueprint/Game/Scene.hpp"

#include <string>
#include <unordered_map>

namespace Blueprint::Game {
class Application;
class SceneManager;

class SceneTypeNotRegistered final : public Core::Exception {
public:
    explicit SceneTypeNotRegistered(const std::string& sceneType);
};

class SceneFabric {
public:
    explicit SceneFabric(Application& application);

public:
    template<class TScene>
    void registerScene(const std::string& keyName);
    [[nodiscard]] Scene* createScene(const std::string& keyName);

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

private:
    Application& m_Application;
    SceneManager& m_SceneManager;
    std::unordered_map<std::string, Scene*(*)(SceneManager&)> m_Creates;
};
} // Blueprint::Game

#include "Blueprint/Game/SceneFabric.inl"

#endif // BLUEPRINT_GAME_SCENE_FABRIC_HPP
