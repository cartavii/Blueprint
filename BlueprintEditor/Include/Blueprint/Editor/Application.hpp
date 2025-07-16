#ifndef BLUEPRINT_EDITOR_APPLICATION_HPP
#define BLUEPRINT_EDITOR_APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace Blueprint::Editor {
class Application final {
public:
    explicit Application(const sf::String& title);

public:
    void run();

    [[nodiscard]] sf::RenderWindow& getRenderWindow();
    [[nodiscard]] const sf::RenderWindow& getRenderWindow() const;

private:
    bool isRunning();
    void processEvents();
    void processEvent(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow m_RenderWindow;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_APPLICATION_HPP
