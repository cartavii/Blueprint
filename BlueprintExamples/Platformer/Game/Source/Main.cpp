#include "Blueprint/Game/Application.hpp"
#include "Platformer/FirstLevel.hpp"
#include "Platformer/LastLevel.hpp"
#include "Platformer/CastleLevelExt.hpp"

int main() {
    try {
        Blueprint::Game::Application application(sf::Vector2u(800, 600), "Today is the");
        {
            Blueprint::Game::SceneFabric& sceneFabric = application.getSceneFabric();
            Blueprint::Game::SceneManager& sceneManager = application.getSceneManager();
            sceneFabric.registerScene<Platformer::CastleLevel>("Platformer::CastleLevel");
            sceneFabric.registerScene<Platformer::FirstLevel>("Platformer::FirstLevel");
            sceneFabric.registerScene<Platformer::LastLevel>("Platformer::LastLevel");
            sceneFabric.registerScene<Platformer::CastleLevelExt>("Platformer::CastleLevelExt");
            sceneManager.loadScene("Main Scene.scenebp");
            for (std::size_t i = 1; ; i++) {
                try {
                    sceneManager.loadScene("Level " + std::to_string(i) + ".scenebp");
                } catch (const Blueprint::Game::SceneInvalidPathException& exception) {
                    break;
                }
            }
            sceneManager.loadScene("Final Scene.scenebp");
            sceneManager.setCurrentScene(sceneManager.getFrontScene());
        }
        application.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
