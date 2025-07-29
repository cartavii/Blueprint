#include "Blueprint/Editor/Application.hpp"

int main() {
    try {
        Blueprint::Editor::Application application("Platformer Editor");
        application.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
