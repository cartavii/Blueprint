#include "Example/Application.hpp"
#include "Example/MyScene.hpp"

Example::Application::Application()
: Blueprint::Editor::Application("Editor Demo") {
    Blueprint::Editor::SceneFabric& sceneFabric = getSceneFabric();
    sceneFabric.registerSceneEditor<MyScene>("Example::MyScene");
}
