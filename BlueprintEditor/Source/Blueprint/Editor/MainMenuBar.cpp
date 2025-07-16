#include "Blueprint/Editor/MainMenuBar.hpp"

#include <imgui.h>

Blueprint::Editor::MainMenuBar::MainMenuBar(Application& application) : m_Application(application) {}

void Blueprint::Editor::MainMenuBar::gui() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::EndMainMenuBar();
    }
}

Blueprint::Editor::Application& Blueprint::Editor::MainMenuBar::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::MainMenuBar::getApplication() const {
    return m_Application;
}
