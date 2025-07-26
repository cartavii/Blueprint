#include "Example/Application.hpp"
#include "Example/MyScene.hpp"

Example::Application::Application()
: Blueprint::Editor::Application("Editor Demo")
, m_EditorPalette({}) {
    Blueprint::Editor::SceneFabric& sceneFabric = getSceneFabric();
    sceneFabric.registerSceneEditor<MyScene>("Example::MyScene");
    Blueprint::Editor::PaletteWindow& paletteWindow = getWindowManager().getEditorPaletteWindow();
    Blueprint::Resources::TextureManager& textureManager = getTextureManager();
    m_EditorPalette = {{textureManager.getTextureResource("Icon 1.png"), "Icon 1"},
                       {textureManager.getTextureResource("Icon 2.png"), "Icon 2"}};
    paletteWindow.setPalette(&m_EditorPalette);
}

Example::Application::~Application() {}
