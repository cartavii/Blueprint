#ifndef PLATFORMER_GAME_CAMERA_SHAKER_HPP
#define PLATFORMER_GAME_CAMERA_SHAKER_HPP

namespace Platformer {
class Camera;

class CameraShaker {
public:
    explicit CameraShaker(Camera& camera);

public:
    void initializeShake();

    [[nodiscard]] bool isShaking() const;

    void update(float deltaTime);

private:
    Camera&     m_Camera;
    const float m_Duration;
    const float m_Magnitude;
    float       m_Elapsed;
    bool        m_Shaking;
};
} // Platformer

#endif // PLATFORMER_GAME_CAMERA_SHAKER_HPP
