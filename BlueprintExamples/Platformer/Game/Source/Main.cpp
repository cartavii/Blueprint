#include "Blueprint/Game/Application.hpp"
#include "Platformer/CastleLevel.hpp"

int main() {
    try {
        Blueprint::Game::Application application(sf::Vector2u(800, 600), "Platformer Game");
        {
            Blueprint::Game::SceneFabric& sceneFabric = application.getSceneFabric();
            Blueprint::Game::SceneManager& sceneManager = application.getSceneManager();
            sceneFabric.registerScene<Platformer::CastleLevel>("Platformer::CastleLevel");
            sceneManager.loadScene("Main Scene.scenebp");
            sceneManager.loadScene("Level 1.scenebp");
            sceneManager.setCurrentScene(sceneManager.getFrontScene());
        }
        application.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
