#ifndef BLUEPRINT_EDITOR_APPLICATION_HPP
#define BLUEPRINT_EDITOR_APPLICATION_HPP

#include "Blueprint/Editor/SceneManager.hpp"
#include "Blueprint/Editor/Gui/WindowManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Blueprint::Editor {
class Application {
public:
    Application();
    virtual ~Application() = default;

public:
    void run();

    [[nodiscard]] virtual SceneManager& getSceneManager() = 0;
    [[nodiscard]] virtual const SceneManager& getSceneManager() const = 0;

    [[nodiscard]] sf::RenderWindow& getRenderWindow();
    [[nodiscard]] const sf::RenderWindow& getRenderWindow() const;

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow m_RenderWindow;
    Gui::WindowManager m_WindowManager;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_APPLICATION_HPP
