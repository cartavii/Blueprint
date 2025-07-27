#include "Blueprint/Editor/Palette.hpp"

Blueprint::Editor::Palette::Palette() : m_SelectedItem(nullptr) {}

Blueprint::Editor::Palette::Palette(const std::initializer_list<Item>& items)
: m_SelectedItem(nullptr)
, m_Items(items) {}

void Blueprint::Editor::Palette::selectItem(const Item* item) {
    m_SelectedItem = item;
}

void Blueprint::Editor::Palette::deselectItem() {
    m_SelectedItem = nullptr;
}

const Blueprint::Editor::Palette::Item* Blueprint::Editor::Palette::getSelectedItem() const {
    return m_SelectedItem;
}

std::size_t Blueprint::Editor::Palette::getItemCount() const {
    return m_Items.size();
}

Blueprint::Editor::Palette::Item& Blueprint::Editor::Palette::getItem(const std::size_t index) {
    return m_Items[index];
}

const Blueprint::Editor::Palette::Item& Blueprint::Editor::Palette::getItem(const std::size_t index) const {
    return m_Items[index];
}

Blueprint::Editor::Palette::iterator Blueprint::Editor::Palette::begin() {
    return m_Items.begin();
}

Blueprint::Editor::Palette::iterator Blueprint::Editor::Palette::end() {
    return m_Items.end();
}

Blueprint::Editor::Palette::constIterator Blueprint::Editor::Palette::begin() const {
    return m_Items.begin();
}

Blueprint::Editor::Palette::constIterator Blueprint::Editor::Palette::end() const {
    return m_Items.end();
}
