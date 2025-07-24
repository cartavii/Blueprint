#include "Blueprint/Editor/SceneFabric.hpp"
#include "Blueprint/Editor/Application.hpp"

Blueprint::Editor::SceneFabric::SceneFabric(Application& application)
: m_Application(application)
, m_TextureManager(application.getTextureManager()){}

Blueprint::Editor::SceneEditor* Blueprint::Editor::SceneFabric::createSceneEditor(const std::string& keyName) {
    const auto it = m_Creates.find(keyName);
    if (it == m_Creates.end()) {
        return nullptr;
    }
    return it->second();
}

Blueprint::Editor::Application& Blueprint::Editor::SceneFabric::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::SceneFabric::getApplication() const {
    return m_Application;
}
