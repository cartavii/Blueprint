#include "Example/Application.hpp"

Example::Application::Application()
: Blueprint::Editor::Application("Editor Demo")
, m_EditorPalette({}) {
    Blueprint::Editor::PaletteWindow& paletteWindow = getWindowManager().getEditorPaletteWindow();
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_EditorPalette = {{textureManager.getTextureResource("Icon 1.png"), "Icon 1"},
                       {textureManager.getTextureResource("Icon 2.png"), "Icon 2"}};
    paletteWindow.setPalette(&m_EditorPalette);
}

Example::Application::~Application() {}
