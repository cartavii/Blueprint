#include "Blueprint/Editor/WindowManager.hpp"
#include "Blueprint/Editor/Application.hpp"

Blueprint::Editor::WindowManager::WindowManager(Application& application)
: m_Application(application)
, m_EditorPaletteWindow(*this)
, m_EditorPalette({}) {
    Resources::TextureManager& textureManager = application.getTextureManager();
    m_EditorPalette = EditorPalette({{textureManager.loadTexture("Icon 1.png"), "Element 12"}, {textureManager.loadTexture("Icon 2.png"), "Element 2"}});
    m_EditorPaletteWindow.setPalette(&m_EditorPalette);
}

void Blueprint::Editor::WindowManager::gui() {
    m_EditorPaletteWindow.show();
}

Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() {
    return m_Application;
}

const Blueprint::Editor::Application& Blueprint::Editor::WindowManager::getApplication() const {
    return m_Application;
}

Blueprint::Editor::EditorPaletteWindow& Blueprint::Editor::WindowManager::getEditorPaletteWindow() {
    return m_EditorPaletteWindow;
}

const Blueprint::Editor::EditorPaletteWindow& Blueprint::Editor::WindowManager::getEditorPaletteWindow() const {
    return m_EditorPaletteWindow;
}
