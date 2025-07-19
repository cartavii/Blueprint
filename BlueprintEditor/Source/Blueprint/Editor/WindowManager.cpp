#include "Blueprint/Editor/WindowManager.hpp"

Blueprint::Editor::WindowManager::WindowManager(Application& application)
: m_Application(application)
, m_EditorPaletteWindow(*this) {}

void Blueprint::Editor::WindowManager::gui() {
    m_EditorPaletteWindow.show();
}

Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() const {
    return m_Application;
}

Blueprint::Editor::PaletteWindow& Blueprint::Editor::WindowManager::getEditorPaletteWindow() {
    return m_EditorPaletteWindow;
}

const Blueprint::Editor::PaletteWindow& Blueprint::Editor::WindowManager::getEditorPaletteWindow() const {
    return m_EditorPaletteWindow;
}
