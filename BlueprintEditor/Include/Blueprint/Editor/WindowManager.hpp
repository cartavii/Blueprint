#ifndef BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
#define BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP

#include "Blueprint/Editor/PaletteWindow.hpp"
#include "Blueprint/Editor/SceneEditorWindow.hpp"

namespace Blueprint::Editor {
class Application;
class WindowManager {
public:
    explicit WindowManager(Application& application);
    ~WindowManager() = default;

public:
    void gui();

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

    [[nodiscard]] PaletteWindow& getEditorPaletteWindow();
    [[nodiscard]] const PaletteWindow& getEditorPaletteWindow() const;

    [[nodiscard]] SceneEditorWindow& getSceneEditorWindow();
    [[nodiscard]] const SceneEditorWindow& getSceneEditorWindow() const;

private:
    Application& m_Application;
    PaletteWindow m_EditorPaletteWindow;
    SceneEditorWindow m_SceneEditorWindow;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
