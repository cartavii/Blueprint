#ifndef EDITOR_SCENE_MANAGER_HPP
#define EDITOR_SCENE_MANAGER_HPP

#include "Blueprint/Editor/SceneManager.hpp"

namespace Editor {
class SceneManager final : public Blueprint::Editor::SceneManager {
public:
    explicit SceneManager(Blueprint::Editor::Application& application);

public:
    void loadScene(const std::filesystem::path& scenePath) override;
};
} // Editor

#endif // EDITOR_SCENE_MANAGER_HPP
