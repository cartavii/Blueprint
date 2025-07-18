#include "Example/MyApplication.hpp"
#include "Example/MyScene.hpp"

Example::MyApplication::MyApplication() : Application(sf::Vector2u(800, 800), "Game works") {
    Blueprint::Game::SceneManager& sceneManager = getSceneManager();
    const std::string sceneType = "Game::MyScene";
    const std::filesystem::path scenePath = "Main Menu.bpscene";
    sceneManager.registerScene<MyScene>(sceneType);
    sceneManager.loadScene(scenePath);
    sceneManager.setCurrentScene(scenePath);
}
