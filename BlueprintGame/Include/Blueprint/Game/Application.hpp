#ifndef BLUEPRINT_GAME_APPLICATION_HPP
#define BLUEPRINT_GAME_APPLICATION_HPP

#include "Blueprint/Game/SceneFabric.hpp"
#include "Blueprint/Game/SceneManager.hpp"
#include "Blueprint/Resources/TextureManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Blueprint::Game {
class Application {
public:
    Application(const sf::Vector2u& windowResolution, const sf::String& windowTitle);

public:
    void run();

    [[nodiscard]] sf::RenderWindow& getRenderWindow();
    [[nodiscard]] const sf::RenderWindow& getRenderWindow() const;

    [[nodiscard]] SceneFabric& getSceneFabric();
    [[nodiscard]] const SceneFabric& getSceneFabric() const;

    [[nodiscard]] SceneManager& getSceneManager();
    [[nodiscard]] const SceneManager& getSceneManager() const;

    [[nodiscard]] Resources::TextureManager& getTextureManager();
    [[nodiscard]] const Resources::TextureManager& getTextureManager() const;

protected:
    bool isRunning();
    void processEvents();
    void processEvent(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow m_RenderWindow;
    Resources::TextureManager m_TextureManager;
    SceneFabric m_SceneFabric;
    SceneManager m_SceneManager;
};
} // Blueprint::Editor

#endif // BLUEPRINT_GAME_APPLICATION_HPP
