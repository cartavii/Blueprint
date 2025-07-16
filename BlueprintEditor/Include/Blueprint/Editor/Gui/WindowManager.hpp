#ifndef BLUEPRINT_EDITOR_GUI_WINDOW_MANAGER_HPP
#define BLUEPRINT_EDITOR_GUI_WINDOW_MANAGER_HPP

#include "Blueprint/Editor/Gui/ScenePaletteWindow.hpp"

namespace Blueprint::Editor::Gui {
class Application;
class WindowManager {
public:
    explicit WindowManager(Application& application);
    ~WindowManager() = default;

public:
    void guiRender();

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

    [[nodiscard]] ScenePaletteWindow& getScenePaletteWindow();
    [[nodiscard]] const ScenePaletteWindow& getScenePaletteWindow() const;

private:
    Application& m_Application;
    ScenePaletteWindow m_scenePaletteWindow;
};
} // Blueprint::Editor::Gui

#endif // BLUEPRINT_EDITOR_GUI_WINDOW_MANAGER_HPP
