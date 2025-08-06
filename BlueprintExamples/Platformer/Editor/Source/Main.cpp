#include "Blueprint/Editor/Application.hpp"
#include "Platformer/CastleLevel.hpp"

int main() {
    try {
        Blueprint::Editor::Application application("Platformer Editor");
        {
            Blueprint::Editor::SceneFabric& sceneFabric = application.getSceneFabric();
            sceneFabric.registerSceneEditor<Platformer::CastleLevel>("Platformer::CastleLevel");
        }
        application.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
