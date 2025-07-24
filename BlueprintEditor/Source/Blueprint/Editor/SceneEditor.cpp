#include "Blueprint/Editor/SceneEditor.hpp"

Blueprint::Editor::SceneEditor::SceneEditor()
: m_TextureManager(nullptr) {}

Blueprint::Editor::Palette* Blueprint::Editor::SceneEditor::getPalette() {
    return nullptr;
}

Blueprint::Resources::TextureManager& Blueprint::Editor::SceneEditor::getTextureManager() {
    return *m_TextureManager;
}

const Blueprint::Resources::TextureManager& Blueprint::Editor::SceneEditor::getTextureManager() const {
    return *m_TextureManager;
}
