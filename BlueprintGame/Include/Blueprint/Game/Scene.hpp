#ifndef BLUEPRINT_GAME_SCENE_HPP
#define BLUEPRINT_GAME_SCENE_HPP

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

namespace Blueprint::Game {
class SceneManager;
class Scene {
public:
    explicit Scene(SceneManager& manager);
    virtual ~Scene() = default;

public:
    virtual void load(const nlohmann::ordered_json& data) {}
    virtual void save(nlohmann::ordered_json& data) {}

    virtual void update(const sf::Time& deltaTime) {}
    virtual void render(sf::RenderTarget& renderTarget) {}

    [[nodiscard]] SceneManager& getSceneManager();
    [[nodiscard]] const SceneManager& getSceneManager() const;

private:
    SceneManager& m_Manager;
};
} // Blueprint::Editor

#endif // BLUEPRINT_GAME_SCENE_HPP
