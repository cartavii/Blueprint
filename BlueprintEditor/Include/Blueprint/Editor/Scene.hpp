#ifndef BLUEPRINT_EDITOR_SCENE_HPP
#define BLUEPRINT_EDITOR_SCENE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <filesystem>

namespace Blueprint::Editor {
class ScenePalette;
namespace Gui {
    class SceneTreeRenderer;
} // Gui
class Scene {
public:
    explicit Scene(const std::filesystem::path& path);
    virtual ~Scene() = default;

public:
    virtual void load() = 0;
    virtual void save() = 0;

    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void render(sf::RenderTarget& renderTarget) = 0;

    void updatePath(const std::filesystem::path& newPath);

    [[nodiscard]] virtual ScenePalette* getPalette() = 0;
    [[nodiscard]] virtual const ScenePalette* getPalette() const = 0;

    [[nodiscard]] virtual Gui::SceneTreeRenderer* getTreeRenderer() = 0;
    [[nodiscard]] virtual const Gui::SceneTreeRenderer* getTreeRenderer() const = 0;

    [[nodiscard]] const std::filesystem::path& getPath() const;

private:
    std::filesystem::path m_Path;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_HPP
