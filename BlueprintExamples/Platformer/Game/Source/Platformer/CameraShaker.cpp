#include "Platformer/CameraShaker.hpp"
#include "Platformer/Camera.hpp"

#include <cstdlib>
#include <ctime>

Platformer::CameraShaker::CameraShaker(Camera& camera)
: m_Camera(camera)
, m_Duration(4.f)
, m_Magnitude(6.f)
, m_Elapsed(0.f)
, m_Shaking(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Platformer::CameraShaker::initializeShake() {
    m_Shaking = true;
    m_Elapsed = 0.f;
}

bool Platformer::CameraShaker::isShaking() const {
    return m_Shaking;
}

void Platformer::CameraShaker::update(const float deltaTime) {
    if (!isShaking()) {
        return;
    }
    m_Elapsed += deltaTime;
    if (m_Elapsed >= m_Duration) {
        m_Shaking = false;
        return;
    }
    const float progress         = m_Elapsed / m_Duration;
    const float currentMagnitude = m_Magnitude * (1.f - progress);
    sf::Vector2f offset;
    offset.x = (rand() / (RAND_MAX / 2.0f) - 1.0f) * currentMagnitude;
    offset.y = (rand() / (RAND_MAX / 2.0f) - 1.0f) * currentMagnitude;
    sf::View& view = m_Camera.getView();
    view.setCenter(view.getCenter() + offset);
}
