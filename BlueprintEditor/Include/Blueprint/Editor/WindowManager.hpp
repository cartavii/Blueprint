#ifndef BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
#define BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP

#include "Blueprint/Editor/PaletteWindow.hpp"

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

private:
    Application& m_Application;
    PaletteWindow m_EditorPaletteWindow;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
