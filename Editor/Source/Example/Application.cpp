#include "Example/Application.hpp"

Example::Application::Application()
: Blueprint::Editor::Application("Editor Demo")
, m_EditorPalette({}) {
    Blueprint::Editor::EditorPaletteWindow& paletteWindow = getWindowManager().getEditorPaletteWindow();
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_EditorPalette = {{textureManager.loadTexture("Icon 1.png"), "Icon 1"},
                          {textureManager.loadTexture("Icon 2.png"), "Icon 2"}};
    paletteWindow.setPalette(&m_EditorPalette);
}

Example::Application::~Application() {
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    for (auto [texture, name] : m_EditorPalette) {
        textureManager.unloadTexture(texture);
    }
}
