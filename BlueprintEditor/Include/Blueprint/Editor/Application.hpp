#ifndef BLUEPRINT_EDITOR_APPLICATION_HPP
#define BLUEPRINT_EDITOR_APPLICATION_HPP

#include "Blueprint/Editor/GuiApi.hpp"
#include "Blueprint/Editor/MainMenuBar.hpp"
#include "Blueprint/Editor/WindowManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Blueprint::Editor {
class Application final {
public:
    explicit Application(const sf::String& title);

public:
    void run();

    [[nodiscard]] sf::RenderWindow& getRenderWindow();
    [[nodiscard]] const sf::RenderWindow& getRenderWindow() const;

    [[nodiscard]] MainMenuBar& getMainMenuBar();
    [[nodiscard]] const MainMenuBar& getMainMenuBar() const;

    [[nodiscard]] WindowManager& getWindowManager();
    [[nodiscard]] const WindowManager& getWindowManager() const;

private:
    bool isRunning();
    void processEvents();
    void processEvent(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow m_RenderWindow;
    GuiApi m_GuiApi;
    MainMenuBar m_MainMenuBar;
    WindowManager m_WindowManager;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_APPLICATION_HPP
