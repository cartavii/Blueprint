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
    void guiItemIcon(const Palette::Item& item);
    void guiItemName(const char* name);

    [[nodiscard]] constexpr float getScaledIconSize() const;
    [[nodiscard]] constexpr float getScaledSpace() const;

private:
    Palette* m_Palette;
    const float m_IconSize;
    const float m_Space;
    float m_Scale;
};
} // Blueprint::Editor

constexpr float Blueprint::Editor::PaletteWindow::getScaledIconSize() const {
    return m_IconSize * m_Scale;
}

constexpr float Blueprint::Editor::PaletteWindow::getScaledSpace() const {
    return m_Space * m_Scale;
}

#endif // BLUEPRINT_EDITOR_EDITOR_PALETTE_WINDOW_HPP
