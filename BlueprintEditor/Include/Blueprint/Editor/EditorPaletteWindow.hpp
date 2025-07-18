#ifndef BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP
#define BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP

#include "Blueprint/Editor/EditorPalette.hpp"
#include "Blueprint/Editor/Window.hpp"

namespace Blueprint::Editor {
class EditorPaletteWindow final : public Window {
public:
    explicit EditorPaletteWindow(WindowManager& manager);

public:
    void setPalette(EditorPalette* palette);

private:
    void gui() override;
    void guiMenuBar();
    void guiEmpty();
    void guiItem(const EditorPalette::Item& item);

private:
    EditorPalette* m_Palette;
    const float m_IconSize;
    const float m_Space;
    float m_Scale;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP
