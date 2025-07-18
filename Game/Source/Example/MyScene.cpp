#include "Example/MyScene.hpp"
#include "Blueprint/Game/Application.hpp"

Example::MyScene::MyScene(Blueprint::Game::SceneManager& manager, const std::filesystem::path& path)
: Scene(manager, path)
, m_Texture(nullptr)
, m_RotationSpeed(60.f) {}

Example::MyScene::~MyScene() {
    getSceneManager().getApplication().getTextureManager().unloadTexture(m_Texture);
}

void Example::MyScene::load(const nlohmann::json& data) {
    const sf::View view = getSceneManager().getApplication().getRenderWindow().getView();
    sf::Vector2f center = view.getSize();
    float size = std::min(center.x, center.y);
    center /= 2.f;
    size /= 2.f;
    m_Rectangle.setPosition(center);
    m_Rectangle.setOrigin(sf::Vector2f(size, size) / 2.f);
    m_Rectangle.setSize(sf::Vector2f(size, size));
    if (const std::string textureNameField = "ImagePath"; data.contains(textureNameField)) {
        const std::string texturePath = data[textureNameField].get<std::string>();
        m_Texture = getSceneManager().getApplication().getTextureManager().loadTexture(texturePath);
    }
    m_Rectangle.setTexture(m_Texture);
}

void Example::MyScene::save(nlohmann::json& data) const {}

void Example::MyScene::update(const sf::Time& deltaTime) {
    m_Rectangle.rotate(sf::degrees(deltaTime.asSeconds() * m_RotationSpeed));
}

void Example::MyScene::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_Rectangle);
}
