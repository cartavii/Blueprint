#include "Blueprint/Game/Application.hpp"

int main() {
    try {
        Blueprint::Game::Application application(sf::Vector2u(800, 600), "Platformer Game");
        application.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
