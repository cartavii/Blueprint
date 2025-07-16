#include "Blueprint/Editor/Application.hpp"

Blueprint::Editor::Application::Application(const sf::String& title)
: m_RenderWindow(sf::VideoMode::getDesktopMode(), title) {}

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
}

void Blueprint::Editor::Application::update() {}

void Blueprint::Editor::Application::render() {
    m_RenderWindow.clear();
    m_RenderWindow.display();
}
