#ifndef PLATFORMER_GAME_HINT_HPP
#define PLATFORMER_GAME_HINT_HPP

#include "Platformer/SpriteObject.hpp"

namespace Platformer {
class Hint final : public SpriteObject {
public:
    Hint();

public:
    void update(float deltaTime);

    void setPosition(const sf::Vector2f& position);

private:
    const float        m_FrameDuration;
    const sf::Vector2f m_Offset;
    float              m_Elapsed;
    int m_Frame = 0;
};
}

#endif // PLATFORMER_GAME_HINT_HPP
