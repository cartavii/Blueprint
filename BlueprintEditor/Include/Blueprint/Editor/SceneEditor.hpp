#ifndef BLUEPRINT_EDITOR_SCENE_EDITOR_HPP
#define BLUEPRINT_EDITOR_SCENE_EDITOR_HPP

#include "Blueprint/Editor/Palette.hpp"

#include <nlohmann/json.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Blueprint::Editor {
class SceneFabric;
class SceneEditor {
public:
    explicit SceneEditor();
    virtual ~SceneEditor() = default;

public:
    virtual void save(const nlohmann::json& data) {}
    virtual void load(nlohmann::json& data) {}

    virtual void update() {}
    virtual void render(sf::RenderTarget& renderTarget) {}

    virtual void onFocusGain() {}
    virtual void onFocusLoss() {}
    
    virtual void onItemSelect(const Palette::Item* item) {}

    [[nodiscard]] virtual Palette* getPalette();

    [[nodiscard]] Resources::TextureManager& getTextureManager();
    [[nodiscard]] const Resources::TextureManager& getTextureManager() const;

private:
    Resources::TextureManager* m_TextureManager;

    friend SceneFabric;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_EDITOR_HPP
