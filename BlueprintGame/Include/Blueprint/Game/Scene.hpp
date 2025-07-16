#ifndef BLUEPRINT_GAME_SCENE_HPP
#define BLUEPRINT_GAME_SCENE_HPP

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

namespace Blueprint::Game {
class SceneManager;
class Scene {
public:
    Scene(SceneManager& manager, const std::filesystem::path& path);
    virtual ~Scene() = default;

public:
    virtual void load(const nlohmann::json& data) = 0;
    virtual void save(nlohmann::json& data) const = 0;

    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void render(sf::RenderTarget& renderTarget) = 0;

    [[nodiscard]] SceneManager& getSceneManager();
    [[nodiscard]] const SceneManager& getSceneManager() const;
    [[nodiscard]] const std::filesystem::path& getPath() const;

private:
    SceneManager& m_Manager;
};
} // Blueprint::Editor

#endif // BLUEPRINT_GAME_SCENE_HPP
