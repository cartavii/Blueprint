#ifndef PLATFORMER_GAME_RANDOS_HOLDER_HPP
#define PLATFORMER_GAME_RANDOS_HOLDER_HPP

#include "Platformer/Rando.hpp"

#include <vector>

namespace Platformer {
class RandosHolder {
public:
    explicit RandosHolder(CastleLevel& castleLevel);

    ~RandosHolder();

public:
    void load(const nlohmann::ordered_json& data);

    void update(float deltaTime);

    void render(sf::RenderTarget& renderTarget);

private:
    CastleLevel& m_CastleLevel;
    Blueprint::Resources::TextureResource m_Resource;
    std::vector<Rando*> m_Randos;
};
} // Platformer

#endif // PLATFORMER_GAME_RANDOS_HOLDER_HPP
