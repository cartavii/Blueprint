#ifndef BLUEPRINT_EDITOR_SCENE_FABRIC_HPP
#define BLUEPRINT_EDITOR_SCENE_FABRIC_HPP

#include "Blueprint/Core/Exception.hpp"
#include "Blueprint/Editor/Palette.hpp"
#include "Blueprint/Editor/SceneEditor.hpp"

#include <string>
#include <unordered_map>

namespace Blueprint::Editor {
class Application;

class SceneTypeNotRegistered final : public Core::Exception {
public:
    explicit SceneTypeNotRegistered(const std::string& sceneType);
};

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
    Resources::TextureManager& m_TextureManager;
    std::unordered_map<std::string, SceneEditor*(*)(Resources::TextureManager&)> m_Creates;
};
} // Blueprint::Editor


template<class TSceneEditor>
void Blueprint::Editor::SceneFabric::registerSceneEditor(const std::string& keyName) {
    m_Creates[keyName] = [](Resources::TextureManager& textureManager) -> SceneEditor* {
        SceneEditor* sceneEditor = new TSceneEditor;
        sceneEditor->m_TextureManager = &textureManager;
        return sceneEditor;
    };
}

#endif // BLUEPRINT_EDITOR_SCENE_FABRIC_HPP
