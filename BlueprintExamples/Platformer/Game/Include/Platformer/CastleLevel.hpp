#ifndef PLATFORMER_GAME_CASTLE_LEVEL_HPP
#define PLATFORMER_GAME_CASTLE_LEVEL_HPP

#include "Platformer/Camera.hpp"
#include "Platformer/CameraShaker.hpp"
#include "Platformer/Door.hpp"
#include "Platformer/Player.hpp"
#include "Platformer/PlayerDead.hpp"
#include "Platformer/TilesHolder.hpp"

#include "Blueprint/Game/Scene.hpp"

#include <optional>

namespace Platformer {
class CastleLevel final : public Blueprint::Game::Scene {
public:
    explicit CastleLevel(Blueprint::Game::SceneManager& manager);

public:
    void load(const nlohmann::ordered_json& data) override;

    void update(const sf::Time& deltaTime) override;

    void render(sf::RenderTarget& renderTarget) override;

    void setPlayerDead();

    void restartScene();

    void setNextScene();

    [[nodiscard]] Camera& getCamera();

    [[nodiscard]] const Camera& getCamera() const;

    [[nodiscard]] CameraShaker& getCameraShaker();

    [[nodiscard]] const CameraShaker& getCameraShaker() const;

    [[nodiscard]] TilesHolder& getGround();

    [[nodiscard]] const TilesHolder& getGround() const;

    [[nodiscard]] TilesHolder& getBlocks();

    [[nodiscard]] const TilesHolder& getBlocks() const;

    [[nodiscard]] Door& getDoor();

    [[nodiscard]] const Door& getDoor() const;

private:
    void loadCamera(const nlohmann::ordered_json& data);

    void loadTiles(const nlohmann::ordered_json& data, TilesHolder& tiles, const std::filesystem::path& texturePath,
                   const char*                   key);

    void loadPlayer(const nlohmann::ordered_json& data);

    void loadDoor(const nlohmann::ordered_json& data);

    void loadNextSceneData(const nlohmann::ordered_json& data);

private:
    Camera                    m_Camera;
    TilesHolder               m_BackGround;
    TilesHolder               m_Ground;
    TilesHolder               m_Blocks;
    Player                    m_Player;
    CameraShaker              m_Shaker;
    std::optional<PlayerDead> m_PlayerDead;
    Door                      m_Door;
    const sf::Color           m_BackgroundColor;
    std::filesystem::path     m_NextScenePath;
};
} // Platformer

#endif // PLATFORMER_GAME_CASTLE_LEVEL_HPP
