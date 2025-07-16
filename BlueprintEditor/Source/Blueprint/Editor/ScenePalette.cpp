#include "Blueprint/Editor/ScenePalette.hpp"

Blueprint::Editor::ScenePalette::ScenePalette() : m_SelectedItem(nullptr) {}

Blueprint::Editor::ScenePalette::ScenePalette(const std::initializer_list<Item*>& items)
: m_SelectedItem(nullptr)
, m_Items(items) {}

Blueprint::Editor::ScenePalette::~ScenePalette() {
    for (const Item* item : m_Items) {
        delete item;
    }
}

void Blueprint::Editor::ScenePalette::setSelected(Item* item) {
    m_SelectedItem = item;
}

void Blueprint::Editor::ScenePalette::deselect() {
    m_SelectedItem = nullptr;
}

Blueprint::Editor::ScenePalette::Item* Blueprint::Editor::ScenePalette::getSelectedItem() {}
