#include "Platformer/Camera.hpp"

Platformer::Camera::Camera()
: m_View(sf::FloatRect(sf::Vector2f(), sf::Vector2f(192, 144)))
, m_LeftMostCenter(m_View.getSize().x / 2.f)
, m_RightMostCenter(0.f) {}

void Platformer::Camera::setRightMostLimit(const float rightMostLimit) {
    m_RightMostCenter = rightMostLimit - m_LeftMostCenter;
}

void Platformer::Camera::setCenter(sf::Vector2f center) {
    if (center.x < m_LeftMostCenter) {
        center.x = m_LeftMostCenter;
    } else if (m_RightMostCenter != 0.f && center.x > m_RightMostCenter) {
        center.x = m_RightMostCenter;
    }
    if (const float halfHeight = m_View.getSize().y / 2.f; center.y != halfHeight) {
        center.y = halfHeight;
    }
    m_View.setCenter(center);
}

sf::Vector2f Platformer::Camera::getCenter() const {
    return m_View.getCenter();
}

sf::View& Platformer::Camera::getView() {
    return m_View;
}

const sf::View& Platformer::Camera::getView() const {
    return m_View;
}
