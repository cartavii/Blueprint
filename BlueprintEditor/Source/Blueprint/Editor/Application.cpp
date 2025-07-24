#include "Blueprint/Editor/Application.hpp"

Blueprint::Editor::Application::Application(const sf::String& title)
: m_RenderWindow(sf::VideoMode::getDesktopMode(), title)
, m_SceneFabric(*this)
, m_SceneManager(*this)
, m_GuiApi(m_RenderWindow)
, m_MainMenuBar(*this)
, m_WindowManager(*this) {}

void Blueprint::Editor::Application::run() {
    while (isRunning()) {
        processEvents();
        update();
        render();
    }
}

sf::RenderWindow& Blueprint::Editor::Application::getRenderWindow() {
    return m_RenderWindow;
}

const sf::RenderWindow& Blueprint::Editor::Application::getRenderWindow() const {
    return m_RenderWindow;
}

Blueprint::Resources::TextureManager& Blueprint::Editor::Application::getTextureManager() {
    return m_TextureManager;
}

const Blueprint::Resources::TextureManager& Blueprint::Editor::Application::getTextureManager() const {
    return m_TextureManager;
}

Blueprint::Editor::SceneFabric& Blueprint::Editor::Application::getSceneFabric() {
    return m_SceneFabric;
}

const Blueprint::Editor::SceneFabric& Blueprint::Editor::Application::getSceneFabric() const {
    return m_SceneFabric;
}

Blueprint::Editor::SceneManager& Blueprint::Editor::Application::getSceneManager() {
    return m_SceneManager;
}

const Blueprint::Editor::SceneManager& Blueprint::Editor::Application::getSceneManager() const {
    return m_SceneManager;
}

Blueprint::Editor::MainMenuBar& Blueprint::Editor::Application::getMainMenuBar() {
    return m_MainMenuBar;
}

const Blueprint::Editor::MainMenuBar& Blueprint::Editor::Application::getMainMenuBar() const {
    return m_MainMenuBar;
}

Blueprint::Editor::WindowManager& Blueprint::Editor::Application::getWindowManager() {
    return m_WindowManager;
}

const Blueprint::Editor::WindowManager& Blueprint::Editor::Application::getWindowManager() const {
    return m_WindowManager;
}

bool Blueprint::Editor::Application::isRunning() {
    return m_RenderWindow.isOpen();
}

void Blueprint::Editor::Application::processEvents() {
    while (const std::optional<sf::Event> event = m_RenderWindow.pollEvent()) {
        processEvent(event.value());
    }
}

void Blueprint::Editor::Application::processEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        m_RenderWindow.close();
    }
    m_GuiApi.processEvent(event);
}

void Blueprint::Editor::Application::update() {
    m_GuiApi.update();
    m_MainMenuBar.gui();
    m_WindowManager.gui();
}

void Blueprint::Editor::Application::render() {
    m_RenderWindow.clear();
    m_GuiApi.render();
    m_RenderWindow.display();
}
