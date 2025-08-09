#ifndef PLATFORMER_GAME_HEDGEHOG_HPP
#define PLATFORMER_GAME_HEDGEHOG_HPP

#include "Platformer/PhysicObject.hpp"

namespace Platformer {
class CastleLevelExt;
class Player;

class Hedgehog : public PhysicObject {
public:
    explicit Hedgehog(CastleLevelExt& castleLevel);

public:
    void load(const nlohmann::ordered_json& data) override;

    virtual void update(float deltaTime);

    virtual void render(sf::RenderTarget& renderTarget);

private:
    CastleLevelExt& m_CastleLevel;
    Player&         m_Player;
    const float     m_FrameDuration;
    float           m_Elapsed;
    int             m_Frame;
    const float     m_HorizontalSpeed;
    float           m_Direction;
};
} // Platformer

#endif // PLATFORMER_GAME_HEDGEHOG_HPP
