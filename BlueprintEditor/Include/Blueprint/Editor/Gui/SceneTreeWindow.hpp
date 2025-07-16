#ifndef BLUEPRINT_EDITOR_GUI_SCENE_TREE_WINDOW_HPP
#define BLUEPRINT_EDITOR_GUI_SCENE_TREE_WINDOW_HPP

#include "Blueprint/Editor/Gui/Window.hpp"

namespace Blueprint::Editor::Gui {
class SceneTreeRenderer;
class SceneTreeWindow final : public Window {
public:
    explicit SceneTreeWindow(bool isOpen = false);

private:
    void guiRender() override;

private:
    SceneTreeRenderer* m_TreeRenderer;
};
} // Blueprint::Editor::Gui

#endif // BLUEPRINT_EDITOR_GUI_SCENE_TREE_WINDOW_HPP
