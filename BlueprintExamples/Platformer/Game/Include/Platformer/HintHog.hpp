#ifndef PLATFORMER_GAME_HINT_HOG_HPP
#define PLATFORMER_GAME_HINT_HOG_HPP

#include "Platformer/Hedgehog.hpp"
#include "Platformer/Hint.hpp"

namespace Platformer {
class HintHog final : public Hedgehog {
public:
    explicit HintHog(CastleLevelExt& castleLevel);

public:
    void update(float deltaTime) override;

    void render(sf::RenderTarget& renderTarget) override;

    [[nodiscard]] Hint& getHint();

private:
    Hint m_Hint;
};
}

#endif // PLATFORMER_GAME_HINT_HOG_HPP
