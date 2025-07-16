#ifndef BLUEPRINT_EDITOR_GUI_SCENE_TREE_RENDERER_HPP
#define BLUEPRINT_EDITOR_GUI_SCENE_TREE_RENDERER_HPP

namespace Blueprint::Editor::Gui {
class SceneTreeRenderer {
public:
    virtual ~SceneTreeRenderer() = default;

public:
    virtual void guiTreeRender() = 0;
};
} // Blueprint::Editor::Gui

#endif // BLUEPRINT_EDITOR_GUI_SCENE_TREE_RENDERER_HPP
