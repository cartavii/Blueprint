#ifndef BLUEPRINT_EDITOR_GUI_SCENE_PALETTE_WINDOW_HPP
#define BLUEPRINT_EDITOR_GUI_SCENE_PALETTE_WINDOW_HPP

#include "Blueprint/Editor/Gui/Window.hpp"
#include "Blueprint/Editor/ScenePalette.hpp"

namespace Blueprint::Editor::Gui {
class ScenePaletteWindow final : public Window {
public:
    explicit ScenePaletteWindow(bool isOpen = false);

private:
    void guiRender() override;

private:
    ScenePalette* m_Palette;
};
} // Blueprint::Editor::Gui

#endif // BLUEPRINT_EDITOR_GUI_SCENE_PALETTE_WINDOW_HPP
