#include "Platformer/Level.hpp"
#include "Platformer/TilesHolder.hpp"
#include "Platformer/Loader.hpp"

#include <SFML/Window/Mouse.hpp>

Platformer::Level::Level()
: m_View(sf::FloatRect(sf::Vector2f(), sf::Vector2f(256, 192)))
, m_Moving(false) {}

void Platformer::Level::update() {
    updateCameraMovement();
}

void Platformer::Level::updateCameraMovement() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        if (!m_Moving) {
            m_Moving = true;
            m_OldViewCenter = m_View.getCenter();
            m_OldMousePosition = getMousePosition(m_View.getSize());
        } else {
            const sf::Vector2f mouseOffset = m_OldMousePosition - getMousePosition(m_View.getSize());
            m_View.setCenter(m_OldViewCenter + mouseOffset);
        }
    } else {
        m_Moving = false;
    }
}

void Platformer::Level::render(sf::RenderTarget& renderTarget) {
    renderTarget.setView(m_View);
}

bool Platformer::Level::isMouseInsideScreen() const {
    const sf::Vector2f mouseNormalPosition = getMouseNormalPosition();
    return mouseNormalPosition.x >= 0.f && mouseNormalPosition.x <= 1.f
        && mouseNormalPosition.y >= 0.f && mouseNormalPosition.y <= 1.f;
}

sf::Vector2f Platformer::Level::getTilePosition(sf::Vector2f position) const {
    position.x -= std::fmod(position.x, 16.f) + (position.x < 0.f ? 16.f : 0.f);
    position.y -= std::fmod(position.y, 16.f) + (position.y < 0.f ? 16.f : 0.f);
    return position;
}

sf::Vector2f Platformer::Level::getMouseTilePosition() const {
    return getTilePosition(getMouseViewPosition(m_View));
}

sf::View& Platformer::Level::getView() {
    return m_View;
}

const sf::View& Platformer::Level::getView() const {
    return m_View;
}
