#include "Platformer/Player.hpp"
#include "Platformer/CastleLevel.hpp"
#include "Platformer/Door.hpp"
#include "Platformer/Loader.hpp"

#include "Blueprint/Core/Sign.hpp"
#include "Blueprint/Game/Application.hpp"
#include "Blueprint/Game/SceneManager.hpp"

Platformer::Player::Player(CastleLevel& castleLevel)
: PhysicObject(castleLevel.getGround(), castleLevel.getBlocks(), {16.f, 16.f}, {{-5.f, 4.f}, {10.f, 12.f}})
, m_CastleLevel(castleLevel)
, m_Camera(m_CastleLevel.getCamera())
, m_Origin(sf::Vector2f(8.f, 0.f))
, m_HorizontalSpeed(2.f)
, m_JumpForce(4.5f)
, m_WalkFrame(0.f)
, m_WalkTime(0.f)
, m_WalkSwitchTime(4.f) {
    getRectangle().setOrigin(m_Origin);
}

void Platformer::Player::load(const nlohmann::ordered_json& data) {
    if (data.contains("Position")) {
        setPosition(Loader::loadVector2f(data, "Position") + m_Origin);
    }
    loadTextures();
}

void Platformer::Player::update(const float deltaTime) {
    updateWalking(deltaTime);
    updateGravity(deltaTime);
    updateJump(deltaTime);
    updateDoor();
    updateCamera();
    updateTexture(deltaTime);
}

void Platformer::Player::loadTextures() {
    Blueprint::Resources::TextureManager& textureManager = m_CastleLevel.getSceneManager().getApplication().getTextureManager();
    m_IdleResource = textureManager.getTextureResource("Gorl/Idle.png");
    m_WalkResource = textureManager.getTextureResource("Gorl/Walk.png");
    m_JumpResource = textureManager.getTextureResource("Gorl/Jump.png");
}

void Platformer::Player::updateWalking(const float deltaTime) {
    float direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction++;
    }
    setVelocityX(m_HorizontalSpeed * direction);
    moveX(deltaTime);
}

void Platformer::Player::updateJump(const float deltaTime) {
    if (!isGrounded() || !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        return;
    }
    setGrounded(false);
    setVelocityY(-m_JumpForce);
    moveY(deltaTime);
}

void Platformer::Player::updateCamera() {
    m_Camera.setCenter(sf::Vector2f(getPosition().x, m_Camera.getCenter().y));
}

void Platformer::Player::updateDoor() {
    if (!isGrounded()) {
        return;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        return;
    }
    if (const sf::FloatRect globalBounds = getGlobalBounds();
        globalBounds.findIntersection(m_CastleLevel.getDoor().getBoundingBox())) {
        m_CastleLevel.setNextScene();
    }
}

void Platformer::Player::updateTexture(const float deltaTime) {
    const sf::Vector2f velocity = getVelocity();
    if (velocity.x != 0.f) {
        getRectangle().setScale(sf::Vector2f(Blueprint::Core::signF(velocity.x), 1.f));
    }
    if (!isGrounded()) {
        setTextureResource(m_JumpResource);
        if (velocity.y < 0.f) {
            setTileIndex(sf::Vector2i(0, 0));
        } else {
            setTileIndex(sf::Vector2i(1, 0));
        }
        return;
    }
    if (velocity.x == 0.f) {
        setTextureResource(m_IdleResource);
        setTileIndex(sf::Vector2i(0, 0));
        return;
    }
    const sf::Texture* oldTexture = getRectangle().getTexture();
    setTextureResource(m_WalkResource);
    if (oldTexture != getRectangle().getTexture()) {
        setTileIndex(sf::Vector2i(0, 0));
        m_WalkFrame = 0.f;
        m_WalkTime = 0.f;
    }
    m_WalkTime += deltaTime;
    if (m_WalkTime > m_WalkSwitchTime) {
        const float frames = std::floor(m_WalkTime / m_WalkSwitchTime);
        m_WalkFrame += frames;
        m_WalkTime -= m_WalkSwitchTime * frames;
        setTileIndex(sf::Vector2i(static_cast<int>(m_WalkFrame) % 6, 0));
    }
}
