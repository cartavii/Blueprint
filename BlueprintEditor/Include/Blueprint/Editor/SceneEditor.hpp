#ifndef BLUEPRINT_EDITOR_SCENE_EDITOR_HPP
#define BLUEPRINT_EDITOR_SCENE_EDITOR_HPP

#include "Blueprint/Editor/Palette.hpp"

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Blueprint::Editor {
class SceneFabric;
class SceneEditorWindow;

class SceneEditor {
public:
    explicit SceneEditor();
    virtual ~SceneEditor() = default;

public:
    virtual void load(const nlohmann::json& data) {}
    virtual void save(nlohmann::json& data) {}

    virtual void update() {}
    virtual void render(sf::RenderTarget& renderTarget) {}

    virtual void onFocusGain() {}
    virtual void onFocusLoss() {}
    
    virtual void onItemSelect(const Palette::Item* item) {}

    [[nodiscard]] virtual Palette* getPalette();

    [[nodiscard]] Resources::TextureManager& getTextureManager();
    [[nodiscard]] const Resources::TextureManager& getTextureManager() const;

    [[nodiscard]] const sf::Vector2f& getMouseNormalPosition() const;
    [[nodiscard]] sf::Vector2f getMousePosition(const sf::Vector2f& viewSize) const;
    [[nodiscard]] sf::Vector2f getMouseViewPosition(const sf::View& view) const;

private:
    Resources::TextureManager* m_TextureManager;
    sf::Vector2f m_MouseNormalPosition;

    friend SceneFabric;
    friend SceneEditorWindow;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_EDITOR_HPP
