#include "Blueprint/Editor/EditorPalette.hpp"

const Blueprint::Editor::EditorPalette::Item Blueprint::Editor::EditorPalette::EmptyItem{nullptr, nullptr};

Blueprint::Editor::EditorPalette::EditorPalette(const std::initializer_list<Item>& items)
: m_SelectedItem(EmptyItem)
, m_Items(items) {}

void Blueprint::Editor::EditorPalette::selectItem(const Item item) {
    m_SelectedItem = item;
}

void Blueprint::Editor::EditorPalette::deselectItem() {
    m_SelectedItem = EmptyItem;
}

Blueprint::Editor::EditorPalette::Item Blueprint::Editor::EditorPalette::getSelectedItem() const {
    return m_SelectedItem;
}

std::size_t Blueprint::Editor::EditorPalette::getItemCount() const {
    return m_Items.size();
}

const Blueprint::Editor::EditorPalette::Item& Blueprint::Editor::EditorPalette::getItem(const std::size_t index) const {
    return m_Items[index];
}
