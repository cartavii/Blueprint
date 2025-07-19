#ifndef BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP
#define BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP

#include "Blueprint/Editor/Palette.hpp"
#include "Blueprint/Editor/Window.hpp"

namespace Blueprint::Editor {
class PaletteWindow final : public Window {
public:
    explicit PaletteWindow(WindowManager& manager);

public:
    void setPalette(Palette* palette);

private:
    void gui() override;
    void guiMenuBar();
    void guiEmpty();
    void guiItem(const Palette::Item& item);

private:
    Palette* m_Palette;
    const float m_IconSize;
    const float m_Space;
    float m_Scale;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP
