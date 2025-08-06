#ifndef PLATFORMER_GAME_CAMERA_HPP
#define PLATFORMER_GAME_CAMERA_HPP

#include <SFML/Graphics/View.hpp>

namespace Platformer {
class Camera {
public:
    explicit Camera();

public:
    void setRightMostLimit(float rightMostLimit);

    void setCenter(sf::Vector2f center);
    [[nodiscard]] sf::Vector2f getCenter() const;

    [[nodiscard]] sf::View& getView();
    [[nodiscard]] const sf::View& getView() const;

private:
    sf::View m_View;
    const float m_LeftMostCenter;
    float m_RightMostCenter;
};
} // Platformer

#endif // PLATFORMER_GAME_CAMERA_HPP
