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

const sf::Vector2f& Blueprint::Editor::SceneEditor::getMouseNormalPosition() const {
    return m_MouseNormalPosition;
}

sf::Vector2f Blueprint::Editor::SceneEditor::getMouseViewPosition(const sf::View& view) const {
    const sf::Vector2f viewSize = view.getSize();
    sf::Vector2f mousePosition = m_MouseNormalPosition;
    mousePosition.x *= viewSize.x;
    mousePosition.y *= viewSize.y;
    return mousePosition;
}
