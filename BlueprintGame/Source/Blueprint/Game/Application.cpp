#include "Blueprint/Game/Application.hpp"

Blueprint::Game::Application::Application(const sf::Vector2u& windowResolution, const sf::String& windowTitle)
: m_RenderWindow(sf::VideoMode(windowResolution), windowTitle)
, m_SceneManager(*this) {}

void Blueprint::Game::Application::run() {
    while (isRunning()) {
        processEvents();
        update();
        render();
    }
}

sf::RenderWindow& Blueprint::Game::Application::getRenderWindow() {
    return m_RenderWindow;
}

const sf::RenderWindow& Blueprint::Game::Application::getRenderWindow() const {
    return m_RenderWindow;
}

Blueprint::Game::SceneManager& Blueprint::Game::Application::getSceneManager() {
    return m_SceneManager;
}

const Blueprint::Game::SceneManager& Blueprint::Game::Application::getSceneManager() const {
    return m_SceneManager;
}

Blueprint::Resources::TextureManager& Blueprint::Game::Application::getTextureManager() {
    return m_TextureManager;
}

const Blueprint::Resources::TextureManager& Blueprint::Game::Application::getTextureManager() const {
    return m_TextureManager;
}

bool Blueprint::Game::Application::isRunning() {
    return getRenderWindow().isOpen() && m_SceneManager.isRunning();
}

void Blueprint::Game::Application::processEvents() {
    while (std::optional<sf::Event> event = m_RenderWindow.pollEvent()) {
        processEvent(event.value());
    }
}

void Blueprint::Game::Application::processEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        getRenderWindow().close();
    }
    else if (const sf::Event::KeyPressed* keyData = event.getIf<sf::Event::KeyPressed>()) {
        if (keyData->code == sf::Keyboard::Key::Escape) {
            throw Core::Exception("Escaped");
        }
    }
}

void Blueprint::Game::Application::update() {
    m_SceneManager.update();
}

void Blueprint::Game::Application::render() {
    getRenderWindow().clear();
    m_SceneManager.render();
    getRenderWindow().display();
}
