#ifndef GAME_EXAMPLE_MY_SCENE_HPP
#define GAME_EXAMPLE_MY_SCENE_HPP

#include "Blueprint/Game/Scene.hpp"
#include "Blueprint/Resources/TextureManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace Example {
class MyScene final : public Blueprint::Game::Scene {
public:
    MyScene(Blueprint::Game::SceneManager& manager, const std::filesystem::path& path);
    ~MyScene() override = default;

public:
    void load(const nlohmann::json& data) override;
    void save(nlohmann::json& data) const override;

    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

private:
    sf::RectangleShape m_Rectangle;
    Blueprint::Resources::TextureResource m_TextureResource;
    float m_RotationSpeed;
};
} // Game

#endif // GAME_EXAMPLE_MY_SCENE_HPP
