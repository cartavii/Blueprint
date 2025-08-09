#ifndef PLATFORMER_EDITOR_LEVEL_HPP
#define PLATFORMER_EDITOR_LEVEL_HPP

#include "Blueprint/Editor/SceneEditor.hpp"

namespace Platformer {
class Level : public Blueprint::Editor::SceneEditor {
public:
    Level();

protected:
    void update() override;

    void updateCameraMovement();

    void render(sf::RenderTarget& renderTarget) override;

    [[nodiscard]] bool isMouseInsideScreen() const;

    [[nodiscard]] sf::Vector2f getTilePosition(sf::Vector2f position) const;

    [[nodiscard]] sf::Vector2f getMouseTilePosition() const;

    [[nodiscard]] sf::View& getView();

    [[nodiscard]] const sf::View& getView() const;

private:
    sf::View     m_View;
    sf::Vector2f m_OldViewCenter;
    sf::Vector2f m_OldMousePosition;
    bool         m_Moving;
};
} // Platformer

#endif // PLATFORMER_EDITOR_LEVEL_HPP
