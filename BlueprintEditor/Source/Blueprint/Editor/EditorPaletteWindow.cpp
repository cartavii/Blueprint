#include "Blueprint/Editor/EditorPaletteWindow.hpp"

#include <algorithm>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/Sprite.hpp>

Blueprint::Editor::EditorPaletteWindow::EditorPaletteWindow(WindowManager& manager)
: Window(manager, "Editor Palette", true, ImGuiWindowFlags_MenuBar)
, m_Palette(nullptr)
, m_IconSize(60.f)
, m_Space(10.f)
, m_Scale(1.f) {}

void Blueprint::Editor::EditorPaletteWindow::setPalette(EditorPalette* palette) {
    m_Palette = palette;
}

void Blueprint::Editor::EditorPaletteWindow::gui() {
    if (m_Palette == nullptr || m_Palette->getItemCount() == 0) {
        return guiEmpty();
    }
    guiMenuBar();
    const ImVec2 padding = ImGui::GetContentRegionAvail();
    const int columnsCount = std::max<int>(padding.x / (m_IconSize + m_Space * 2.f) / m_Scale, 1);
    if (!ImGui::BeginTable("Editor Item Table", columnsCount, ImGuiTableFlags_Borders)) {
        return;
    }
    for (std::size_t i = 0; i < m_Palette->getItemCount(); i++) {
        if (i % columnsCount == 0) {
            ImGui::TableNextRow();
        }
        ImGui::TableNextColumn();
        guiItem(m_Palette->getItem(i));
    }
    ImGui::EndTable();
}

void Blueprint::Editor::EditorPaletteWindow::guiMenuBar() {
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

void Blueprint::Editor::EditorPaletteWindow::guiEmpty() {
    const char* text = "Palette is empty";
    const ImVec2 textSize = ImGui::CalcTextSize(text);
    const ImVec2 padding = ImGui::GetContentRegionAvail();
    const ImVec2 position = {(padding.x - textSize.x) * 0.5f, (padding.y - textSize.y) * 0.5f};
    ImGui::SetCursorPos(position);
    ImGui::Text(text);
}

void Blueprint::Editor::EditorPaletteWindow::guiItem(const EditorPalette::Item& item) {
    ImGui::BeginGroup();
    ImGui::PushID(&item);
    ImGuiStyle& style = ImGui::GetStyle();
    const float originalFontScale = style.FontScaleMain;
    const float originalCellPadding = style.CellPadding.x;
    const float originalFramePadding = style.FramePadding.x;
    style.CellPadding.x = 0.f;
    style.FramePadding.x = 0.f;
    style.FontScaleMain *= m_Scale;
    const float scaledSize = m_IconSize * m_Scale;
    const float scaledSpace = m_Space * m_Scale;

    const float columnWidth = ImGui::GetColumnWidth();
    const float buttonOffset = (columnWidth - scaledSize) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + buttonOffset);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + scaledSpace / 2.f);

    const bool isSelectedItem = m_Palette->getSelectedItem().name == item.name;
    if (isSelectedItem) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.59f, 0.98f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
    }
    bool isButtonPressed = false;
    if (item.texture == nullptr) {
        isButtonPressed = ImGui::Button("##Item Button", ImVec2(scaledSize, scaledSize));
    } else {
        const sf::Sprite sprite(*item.texture);
        isButtonPressed = ImGui::ImageButton("##Item Button", sprite, sf::Vector2f(scaledSize, scaledSize));
    }
    if (isSelectedItem) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
    }
    if (isButtonPressed) {
        m_Palette->selectItem(item);
    }

    const float textWidth = ImGui::CalcTextSize(item.name).x;
    const float textOffset = (columnWidth - textWidth) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);
    if (textWidth <= columnWidth) {
        ImGui::Text(item.name);
    } else {
        ImGui::Text("...");
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::TextDisabled(item.name);
            ImGui::EndTooltip();
        }
    }

    style.CellPadding.x = originalCellPadding;
    style.FramePadding.x = originalFramePadding;
    style.FontScaleMain = originalFontScale;
    ImGui::PopID();
    ImGui::EndGroup();
}
