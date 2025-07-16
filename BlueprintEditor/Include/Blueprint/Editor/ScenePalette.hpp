#ifndef BLUEPRINT_EDITOR_SCENE_PALETTE_HPP
#define BLUEPRINT_EDITOR_SCENE_PALETTE_HPP

#include "Blueprint/Resources/TextureManager.hpp"

#include <string>
#include <vector>

namespace Blueprint::Editor {
class ScenePalette {
public:
    struct Item {
        Resources::TextureResource textureResource;
        sf::IntRect textureRect;
        std::string name;
    };

public:
    ScenePalette();
    explicit ScenePalette(const std::initializer_list<Item*>& items);
    ~ScenePalette();

public:
    void setSelected(Item* item);
    void deselect();

    [[nodiscard]] Item* getSelectedItem();
    [[nodiscard]] const Item* getSelectedItem() const;

    using iterator = std::vector<Item*>::iterator;
    using constIterator = std::vector<Item*>::const_iterator;
    iterator begin();
    iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    Item* m_SelectedItem;
    std::vector<Item*> m_Items;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_PALETTE_HPP
