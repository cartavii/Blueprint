#include "Blueprint/Editor/SceneEditorWindow.hpp"
#include "Blueprint/Editor/Application.hpp"
#include "Blueprint/Editor/SceneEditor.hpp"
#include "Blueprint/Editor/SceneManager.hpp"
#include "Blueprint/Editor/WindowManager.hpp"

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderTexture.hpp>

Blueprint::Editor::SceneEditorWindow::SceneEditorWindow(WindowManager& manager)
: Window(manager, "Scene Editor", true, ImGuiWindowFlags_MenuBar)
, ResourceManager("Scenes")
, m_Reload(false)
, m_SceneManager(manager.getApplication().getSceneManager())
, m_SelectedSceneEditor(nullptr)
, m_Watch(getRootPath().string(), [this](const std::string& path, const filewatch::Event event){update(path, event);}) {}

void Blueprint::Editor::SceneEditorWindow::gui() {
    guiMenuBar();
    if (m_Reload) {
        reload();
    }
    if (m_SceneManager.getSceneHolderCount() == 0) {
        return guiEmpty();
    }
    if (m_SelectedSceneEditor == nullptr) {
        m_SelectedSceneEditor = m_SceneManager.begin()->sceneEditor;
    }
    if (!ImGui::BeginTabBar("Scene Editor tab bar", ImGuiTabBarFlags_Reorderable)) {
        return;
    }
    for (auto [sceneEditor, keyName, path] : m_SceneManager) {
        std::string sPath = path.string();
        if (ImGui::BeginTabItem(sPath.c_str())) {
            if (sceneEditor != m_SelectedSceneEditor) {
                if (m_SelectedSceneEditor != nullptr) {
                    m_SelectedSceneEditor->onFocusLoss();
                }
                sceneEditor->onFocusGain();
                m_SelectedSceneEditor = sceneEditor;
            }
            ImVec2 space = ImGui::GetContentRegionAvail();
            if (space.x < 1.f) { space.x = 1.f; }
            if (space.y < 1.f) { space.y = 1.f; }
            m_RenderTexture.resize(sf::Vector2u(space.x, space.y));
            m_RenderTexture.clear();
            sceneEditor->update();
            sceneEditor->render(m_RenderTexture);
            m_RenderTexture.display();
            ImGui::Image(m_RenderTexture);
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
}

void Blueprint::Editor::SceneEditorWindow::guiMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Reload")) {
            m_Reload = true;
        }
        if (ImGui::MenuItem("Exit")) {
            close();
        }
        ImGui::EndMenuBar();
    }
}

void Blueprint::Editor::SceneEditorWindow::guiEmpty() {
}

void Blueprint::Editor::SceneEditorWindow::reload() {
    m_Reload = false;
    m_SelectedSceneEditor = nullptr;
    const std::filesystem::path basePath = "../Resources/Scenes/";
    const std::filesystem::path rootPath = getRootPath();
    m_SceneManager.clear();
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootPath)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        std::filesystem::path normalizedPath = entry.path();
        normalizedPath = std::filesystem::relative(normalizedPath, basePath);
        m_SceneManager.loadSceneEditor(normalizedPath);
    }
}

void Blueprint::Editor::SceneEditorWindow::update(const std::filesystem::path& path, const filewatch::Event event) {}
