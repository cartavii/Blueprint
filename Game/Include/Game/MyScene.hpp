#ifndef GAME_MY_SCENE_HPP
#define GAME_MY_SCENE_HPP

#include "Blueprint/Game/Scene.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Game {
class MyScene final : public Blueprint::Game::Scene {
public:
    MyScene(Blueprint::Game::SceneManager& manager, const std::filesystem::path& path);
    ~MyScene() override;

public:
    void load(const nlohmann::json& data) override;
    void save(nlohmann::json& data) const override;

    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

private:
    sf::RectangleShape m_Rectangle;
    const sf::Texture* m_Texture;
    float m_RotationSpeed;
};
} // Game

#endif // GAME_MY_SCENE_HPP
