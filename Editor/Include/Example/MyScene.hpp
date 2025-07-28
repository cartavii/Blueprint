#ifndef EXAMPLE_MY_SCENE_HPP
#define EXAMPLE_MY_SCENE_HPP

#include "Blueprint/Editor/SceneEditor.hpp"
#include "Blueprint/Resources/TextureManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

namespace Example {
class MyScene final : public Blueprint::Editor::SceneEditor {
public:
    MyScene();

public:
    void load(nlohmann::json& data) override;

    void update() override;
    void render(sf::RenderTarget& renderTarget) override;

    void onFocusGain() override;
    void onFocusLoss() override;

    [[nodiscard]] Blueprint::Editor::Palette* getPalette() override;

private:
    Blueprint::Editor::Palette m_Palette;
    Blueprint::Resources::TextureResource m_TextureResource;
    sf::RectangleShape m_Rectangle;
    sf::Clock m_DeltaClock;
    const float m_RotationSpeed;
};
} // Example

#endif // EXAMPLE_MY_SCENE_HPP
