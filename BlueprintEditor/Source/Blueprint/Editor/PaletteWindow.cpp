#include "Blueprint/Editor/PaletteWindow.hpp"

#include <algorithm>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/Sprite.hpp>

Blueprint::Editor::PaletteWindow::PaletteWindow(WindowManager& manager)
: Window(manager, "Editor Palette", true, ImGuiWindowFlags_MenuBar)
, m_Palette(nullptr)
, m_IconSize(60.f)
, m_Space(10.f)
, m_Scale(1.f) {}

void Blueprint::Editor::PaletteWindow::setPalette(Palette* palette) {
    m_Palette = palette;
}

void Blueprint::Editor::PaletteWindow::gui() {
    guiMenuBar();
    if (m_Palette == nullptr || m_Palette->getItemCount() == 0) {
        return guiEmpty();
    }
    const ImVec2 padding = ImGui::GetContentRegionAvail();
    const int columnsCount = std::max<int>(padding.x / (m_IconSize + m_Space * 2.f) / m_Scale, 1);
    const ImVec2 size(columnsCount * (m_IconSize + m_Space * 2.f) * m_Scale, 0.f);
    if (!ImGui::BeginTable("Editor Item Table", columnsCount, ImGuiTableFlags_None, size)) {
        return;
    }
    for (std::size_t i = 0; i < m_Palette->getItemCount(); i++) {
        if (i % columnsCount == 0) {
            ImGui::TableNextRow();
        }
        ImGui::TableNextColumn();
        guiItem(m_Palette->getItem(i));
    }
    processDeselection();
    ImGui::EndTable();
}

void Blueprint::Editor::PaletteWindow::guiMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Settings")) {
            if (ImGui::BeginMenu("Scale")) {
                if (ImGui::MenuItem("50%", nullptr, m_Scale == 0.5f)) { m_Scale = 0.5f; }
                if (ImGui::MenuItem("100%", nullptr, m_Scale == 1.f)) { m_Scale = 1.f; }
                if (ImGui::MenuItem("150%", nullptr, m_Scale == 1.5f)) { m_Scale = 1.5f; }
                if (ImGui::MenuItem("200%", nullptr, m_Scale == 2.f)) { m_Scale = 2.f; }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Exit")) {
            close();
        }
        ImGui::EndMenuBar();
    }
}

void Blueprint::Editor::PaletteWindow::guiEmpty() {
    const char* text = "Palette is empty";
    const ImVec2 textSize = ImGui::CalcTextSize(text);
    const ImVec2 padding = ImGui::GetContentRegionMax();
    const ImVec2 position = {(padding.x - textSize.x) * 0.5f, (padding.y - textSize.y) * 0.5f + 18.f};
    ImGui::SetCursorPos(position);
    ImGui::Text(text);
}

class PaletteTableStyle {
public:
    PaletteTableStyle(ImGuiStyle& style, const float scale)
    : m_Style(style)
    , m_Scale(scale)
    , m_OriginalFontScale(style.FontScaleMain)
    , m_OriginalCellPadding(style.CellPadding.x)
    , m_OriginalFramePadding(style.FramePadding.x) {
        m_Style.FontScaleMain *= m_Scale;
        m_Style.CellPadding.x = 0.f;
        m_Style.FramePadding.x = 0.f;
    }

    ~PaletteTableStyle() {
        m_Style.FontScaleMain = m_OriginalFontScale;
        m_Style.CellPadding.x = m_OriginalCellPadding;
        m_Style.FramePadding.x = m_OriginalFramePadding;
    }

private:
    ImGuiStyle& m_Style;
    const float m_Scale;
    const float m_OriginalFontScale;
    const float m_OriginalCellPadding;
    const float m_OriginalFramePadding;
};

void Blueprint::Editor::PaletteWindow::guiItem(const Palette::Item& item) {
    PaletteTableStyle style(ImGui::GetStyle(), m_Scale);
    ImGui::BeginGroup();
    ImGui::PushID(&item);
    guiItemIcon(item);
    guiItemName(item.name);
    ImGui::PopID();
    ImGui::EndGroup();
}

class IconStyle {
public:
    explicit IconStyle(const float scale) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.59f, 0.98f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 4.0f * scale);
    }

    ~IconStyle() {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
    }
};

void Blueprint::Editor::PaletteWindow::guiItemIcon(const Palette::Item& item) {
    const float scaledIconSize = getScaledIconSize();
    const float scaledSpace = getScaledSpace();
    const sf::Texture* itemTexture = item.textureResource.getTexture();
    std::optional<IconStyle> style = std::nullopt;

    if (m_Palette->getSelectedItem() == &item) {
        style.emplace(m_Scale);
    }
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + scaledSpace);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + scaledSpace / 2.f);
    bool isButtonPressed = false;
    if (itemTexture == nullptr) {
        isButtonPressed = ImGui::Button("##Item Button", ImVec2(scaledIconSize, scaledIconSize));
    } else {
        const sf::Sprite sprite(*itemTexture);
        isButtonPressed = ImGui::ImageButton("##Item Button", sprite, sf::Vector2f(scaledIconSize, scaledIconSize));
    }
    if (isButtonPressed) {
        m_Palette->selectItem(&item);
    }
}

void Blueprint::Editor::PaletteWindow::guiItemName(const char* name) {
    const float columnWidth = getScaledIconSize() + getScaledSpace() * 2.f;
    float textWidth = ImGui::CalcTextSize(name).x;
    float textOffset = (columnWidth - textWidth) * 0.5f;
    const char* appearName = name;

    if (textWidth >= columnWidth) {
        appearName = "...";
        textWidth = ImGui::CalcTextSize(name).x;
        textOffset = (columnWidth - textWidth) * 0.5f;
    }
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);

    ImGui::Text(appearName);
    if (appearName == "..." && ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::Text(name);
        ImGui::EndTooltip();
    }
}

void Blueprint::Editor::PaletteWindow::processDeselection() {
    if (ImGui::IsMouseClicked(0) && !ImGui::IsAnyItemHovered() && ImGui::IsWindowHovered()) {
        m_Palette->deselectItem();
    }
}
