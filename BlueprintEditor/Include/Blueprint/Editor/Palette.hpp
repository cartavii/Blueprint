#ifndef BLUEPRINT_EDITOR_EDITOR_PALETTE_HPP
#define BLUEPRINT_EDITOR_EDITOR_PALETTE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <vector>

namespace Blueprint::Editor {
class Palette final {
public:
    struct Item {
        const sf::Texture* texture;
        const char* name;
    };
    using iterator = std::vector<Item>::iterator;
    using constIterator = std::vector<Item>::const_iterator;

public:
    Palette(const std::initializer_list<Item>& items);
    ~Palette() = default;

public:
    void selectItem(Item item);
    void deselectItem();
    [[nodiscard]] Item getSelectedItem() const;
    [[nodiscard]] std::size_t getItemCount() const;
    [[nodiscard]] const Item& getItem(std::size_t index) const;

    [[nodiscard]] iterator begin();
    [[nodiscard]] iterator end();
    [[nodiscard]] constIterator begin() const;
    [[nodiscard]] constIterator end() const;

public:
    static const Item EmptyItem;

private:
    Item m_SelectedItem;
    std::vector<Item> m_Items;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_EDITOR_PALETTE_HPP
