#ifndef BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
#define BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP

#include "Blueprint/Editor/EditorPaletteWindow.hpp"

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

    EditorPaletteWindow& getEditorPaletteWindow();
    const EditorPaletteWindow& getEditorPaletteWindow() const;

private:
    Application& m_Application;
    EditorPaletteWindow m_EditorPaletteWindow;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
