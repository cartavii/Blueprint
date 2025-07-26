#include "Example/MyScene.hpp"
#include <SFML/System/Time.hpp>

Example::MyScene::MyScene() {
    onFocusLoss();
}

void Example::MyScene::load(nlohmann::json& data) {
    if (data.contains("ImagePath")) {
        m_TextureResource = getTextureManager().getTextureResource(data["ImagePath"].get<std::filesystem::path>());
        m_Rectangle.setTexture(m_TextureResource.getTexture());
    }
}

void Example::MyScene::update() {
    const sf::Time deltaTime = m_DeltaClock.restart();
    m_Rectangle.rotate(sf::degrees(deltaTime.asSeconds()) * 5.f);
}

void Example::MyScene::render(sf::RenderTarget& renderTarget) {
    const sf::View& view = renderTarget.getView();
    const float size = std::min(view.getSize().x, view.getSize().y) / 2.f;
    m_Rectangle.setSize(sf::Vector2f(size, size));
    m_Rectangle.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
    m_Rectangle.setPosition(view.getSize() / 2.f);
    renderTarget.draw(m_Rectangle);
}

void Example::MyScene::onFocusGain() {
    m_DeltaClock.start();
}

void Example::MyScene::onFocusLoss() {
    m_DeltaClock.stop();
}

