#include "Blueprint/Editor/Application.hpp"
#include "Platformer/FirstLevel.hpp"
#include "Platformer/LastLevel.hpp"
#include "Platformer/CastleLevelExt.hpp"

int main() {
    try {
        Blueprint::Editor::Application application("Platformer Editor");
        {
            Blueprint::Editor::SceneFabric& sceneFabric = application.getSceneFabric();
            sceneFabric.registerSceneEditor<Platformer::CastleLevel>("Platformer::CastleLevel");
            sceneFabric.registerSceneEditor<Platformer::CastleLevelExt>("Platformer::CastleLevelExt");
            sceneFabric.registerSceneEditor<Platformer::FirstLevel>("Platformer::FirstLevel");
            sceneFabric.registerSceneEditor<Platformer::LastLevel>("Platformer::LastLevel");
        }
        application.run();
    } catch (const Blueprint::Core::Exception& exception) {
        exception.log();
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
