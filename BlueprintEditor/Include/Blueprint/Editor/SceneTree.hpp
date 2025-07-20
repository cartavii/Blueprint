#ifndef BLUEPRINT_EDITOR_SCENE_TREE_HPP
#define BLUEPRINT_EDITOR_SCENE_TREE_HPP

#include <memory>
#include <string>
#include <vector>

namespace Blueprint::Editor {
class SceneTree {
public:
    struct Node {
        std::string name;
        std::weak_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
    };
    using iterator = std::vector<Node*>::iterator;
    using constIterator = std::vector<Node*>::const_iterator;

public:
    SceneTree(const std::initializer_list<Node*>& tree);
    ~SceneTree();

public:
    std::shared_ptr<Node> getSelectedNode();
    std::shared_ptr<const Node> getSelectedNode() const;

    std::size_t size();
    iterator begin();
    iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    std::shared_ptr<Node> m_SelectedNode;
    std::vector<std::shared_ptr<Node>> m_Tree;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_SCENE_TREE_HPP
