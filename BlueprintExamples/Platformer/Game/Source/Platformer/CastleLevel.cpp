#include "Platformer/CastleLevel.hpp"

#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/SceneManager.hpp"

Platformer::CastleLevel::CastleLevel(Blueprint::Game::SceneManager& manager)
: Scene(manager)
, m_Player(*this)
, m_BackgroundColor(25, 5, 25) {
    m_Door.setPosition(sf::Vector2f(-16.f, 0.f));
}

void Platformer::CastleLevel::load(const nlohmann::ordered_json& data) {
    loadCamera(data);
    loadTiles(data, m_BackGround, "Back Ground.png", "BackGroundTiles");
    loadTiles(data, m_Ground, "Ground.png", "GroundTiles");
    loadTiles(data, m_Blocks, "Block.png", "BlockTiles");
    loadPlayer(data);
    loadDoor(data);
    loadNextSceneData(data);
}

void Platformer::CastleLevel::update(const sf::Time& deltaTime) {
    const float dt = deltaTime.asSeconds() * 60.f;
    m_Player.update(dt);
}

void Platformer::CastleLevel::render(sf::RenderTarget& renderTarget) {
    renderTarget.setView(m_Camera.getView());
    renderTarget.clear(m_BackgroundColor);
    m_BackGround.render(renderTarget);
    m_Ground.render(renderTarget);
    m_Blocks.render(renderTarget);
    m_Door.render(renderTarget);
    m_Player.render(renderTarget);
}

void Platformer::CastleLevel::setNextScene() {
    Blueprint::Game::SceneManager& sceneManager = getSceneManager();
    sceneManager.unloadScene(*this);
    if (const std::filesystem::path nextPath = sceneManager.getFrontScene(); !nextPath.empty()) {
        sceneManager.setCurrentScene(nextPath);
    } else {
        sceneManager.resetCurrentScene();
    }
}

Platformer::Camera& Platformer::CastleLevel::getCamera() {
    return m_Camera;
}

const Platformer::Camera& Platformer::CastleLevel::getCamera() const {
    return m_Camera;
}

Platformer::TilesHolder& Platformer::CastleLevel::getGround() {
    return m_Ground;
}

const Platformer::TilesHolder& Platformer::CastleLevel::getGround() const {
    return m_Ground;
}

Platformer::TilesHolder& Platformer::CastleLevel::getBlocks() {
    return m_Blocks;
}

const Platformer::TilesHolder& Platformer::CastleLevel::getBlocks() const {
    return m_Blocks;
}

Platformer::Door& Platformer::CastleLevel::getDoor() {
    return m_Door;
}

const Platformer::Door& Platformer::CastleLevel::getDoor() const {
    return m_Door;
}

void Platformer::CastleLevel::loadCamera(const nlohmann::ordered_json& data) {
    if (data.contains("StopCamera")) {
        m_Camera.setRightMostLimit(data["StopCamera"].get<float>());
    }
}

void Platformer::CastleLevel::loadTiles(const nlohmann::ordered_json& data, TilesHolder& tiles, const std::filesystem::path& texturePath, const char* key) {
    if (!data.contains(key)) {
        return;
    }
    Blueprint::Resources::TextureManager& textureManager = getSceneManager().getApplication().getTextureManager();
    tiles.setTextureResource(textureManager.getTextureResource(texturePath));
    tiles.load(data[key]);
}

void Platformer::CastleLevel::loadPlayer(const nlohmann::ordered_json& data) {
    if (data.contains("Player")) {
        m_Player.load(data["Player"]);
    }
}

void Platformer::CastleLevel::loadDoor(const nlohmann::ordered_json& data) {
    Blueprint::Resources::TextureManager& textureManager = getSceneManager().getApplication().getTextureManager();
    m_Door.setTextureResource(textureManager.getTextureResource("Door.png"));
    if (data.contains("Door")) {
        m_Door.load(data["Door"]);
    }
}


void Platformer::CastleLevel::loadNextSceneData(const nlohmann::ordered_json& data) {
    if (data.contains("NextScene")) {
        m_NextScenePath = data["NextScene"].get<std::filesystem::path>();
        getSceneManager().loadScene(m_NextScenePath);
    }
}
