#ifndef BLUEPRINT_EDITOR_SCENE_MANAGER_HPP
#define BLUEPRINT_EDITOR_SCENE_MANAGER_HPP

#include "Blueprint/Editor/Scene.hpp"

#include <vector>

namespace Blueprint::Editor {
class Application;
class SceneManager {
public:
    explicit SceneManager(Application& application);
    virtual ~SceneManager();

public:
    virtual void loadScene(const std::filesystem::path& scenePath) = 0;
    void unloadScene(const std::filesystem::path& scenePath);

private:
    Scene* m_CurrentScene;
    std::vector<Scene*> m_Scenes;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_MANAGER_HPP
