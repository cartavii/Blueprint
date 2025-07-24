#ifndef BLUEPRINT_EDITOR_SCENE_FABRIC_HPP
#define BLUEPRINT_EDITOR_SCENE_FABRIC_HPP

#include "Blueprint/Editor/Palette.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace Blueprint::Editor {
class Application;
class SceneEditor;
class SceneFabric {
public:
    explicit SceneFabric(Application& application);

public:
    template<class TSceneEditor>
    void registerSceneEditor(const std::string& keyName);
    [[nodiscard]] SceneEditor* createSceneEditor(const std::string& keyName);

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

private:
    Application& m_Application;
    Resources::TextureManager m_TextureManager;
    std::unordered_map<std::string, SceneEditor*(*)()> m_Creates;
};
} // Blueprint::Editor


template<class TSceneEditor>
void Blueprint::Editor::SceneFabric::registerSceneEditor(const std::string& keyName) {
    m_Creates[keyName] = [&]() -> SceneEditor* {
        SceneEditor* sceneEditor = new TSceneEditor(m_TextureManager);
        sceneEditor->m_TextureManager = &m_TextureManager;
        return sceneEditor;
    };
}

#endif // BLUEPRINT_EDITOR_SCENE_FABRIC_HPP
