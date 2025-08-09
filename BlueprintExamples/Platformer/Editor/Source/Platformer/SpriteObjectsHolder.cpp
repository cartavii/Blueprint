#include "Platformer/SpriteObjectsHolder.hpp"

Platformer::SpriteObjectsHolder::~SpriteObjectsHolder() {
    for (const SpriteObject* spriteObject: m_SpriteObjects) {
        delete spriteObject;
    }
}

void Platformer::SpriteObjectsHolder::setTextureResource(const Blueprint::Resources::TextureResource& textureResource) {
    m_Resource = textureResource;
    for (SpriteObject* spriteObject: m_SpriteObjects) {
        spriteObject->setTextureResource(m_Resource);
    }
}

void Platformer::SpriteObjectsHolder::load(const nlohmann::ordered_json& data) {
    for (const nlohmann::ordered_json& spriteObjectData: data) {
        SpriteObject* spriteObject = new SpriteObject();
        spriteObject->setTextureResource(m_Resource);
        spriteObject->load(spriteObjectData);
        m_SpriteObjects.push_back(spriteObject);
    }
}

void Platformer::SpriteObjectsHolder::save(nlohmann::ordered_json& data) {
    for (SpriteObject* spriteObject: m_SpriteObjects) {
        nlohmann::ordered_json spriteObjectData;
        spriteObject->save(spriteObjectData);
        data.push_back(spriteObjectData);
    }
}

#include <iostream>

void Platformer::SpriteObjectsHolder::updateAdd(const sf::Vector2f& mousePosition) {
    for (const SpriteObject* spriteObject: m_SpriteObjects) {
        if (spriteObject->getPosition() == mousePosition) {
            return;
        }
    }
    SpriteObject* spriteObject = new SpriteObject();
    spriteObject->setTextureResource(m_Resource);
    spriteObject->setPosition(mousePosition);
    m_SpriteObjects.push_back(spriteObject);
    std::cout << "Rando was here\n";
}

void Platformer::SpriteObjectsHolder::updateRemove(const sf::Vector2f& mousePosition) {
    for (auto it = m_SpriteObjects.begin(); it != m_SpriteObjects.end(); ++it) {
        if ((*it)->getPosition() == mousePosition) {
            delete *it;
            m_SpriteObjects.erase(it);
            return;
        }
    }
}

void Platformer::SpriteObjectsHolder::render(sf::RenderTarget& renderTarget) {
    for (SpriteObject* spriteObject: m_SpriteObjects) {
        spriteObject->render(renderTarget);
    }
}
