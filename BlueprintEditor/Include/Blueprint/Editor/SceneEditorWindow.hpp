#ifndef BLUEPRINT_EDITOR_SCENE_EDITOR_WINDOW_HPP
#define BLUEPRINT_EDITOR_SCENE_EDITOR_WINDOW_HPP

#include "Blueprint/Editor/Window.hpp"
#include "Blueprint/Resources/ResourceManager.hpp"

#include <filewatch/FileWatch.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <filesystem>

namespace Blueprint::Editor {
class SceneManager;
class SceneEditor;
class SceneEditorWindow final : public Window, private Resources::ResourceManager {
public:
    explicit SceneEditorWindow(WindowManager& manager);

private:
    void gui() override;
    void guiMenuBar();
    void guiEmpty();

private:
    void reload();
    void update(const std::filesystem::path& path, filewatch::Event event);

private:
    bool m_Reload;
    SceneManager& m_SceneManager;
    SceneEditor* m_SelectedSceneEditor;
    filewatch::FileWatch<std::string> m_Watch;
    sf::RenderTexture m_RenderTexture;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_EDITOR_WINDOW_HPP
