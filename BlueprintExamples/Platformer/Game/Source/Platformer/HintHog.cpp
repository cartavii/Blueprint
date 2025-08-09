#include "Platformer/HintHog.hpp"

Platformer::HintHog::HintHog(CastleLevelExt& castleLevel) : Hedgehog(castleLevel) {}

void Platformer::HintHog::update(const float deltaTime) {
    Hedgehog::update(deltaTime);
    m_Hint.update(deltaTime);
    m_Hint.setPosition(getPosition());
}

Platformer::Hint& Platformer::HintHog::getHint() {
    return m_Hint;
}

void Platformer::HintHog::render(sf::RenderTarget& renderTarget) {
    Hedgehog::render(renderTarget);
    m_Hint.render(renderTarget);
}
