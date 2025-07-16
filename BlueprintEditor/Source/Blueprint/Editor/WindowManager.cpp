#include "Blueprint/Editor/WindowManager.hpp"

#include <imgui.h>

Blueprint::Editor::WindowManager::WindowManager(Application& application)
: m_Application(application) {}

void Blueprint::Editor::WindowManager::gui() {
    ImGui::ShowDemoWindow();
}

Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() const {
    return m_Application;
}
