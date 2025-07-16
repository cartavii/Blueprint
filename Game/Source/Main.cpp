#include "Game/MyApplication.hpp"
#include <exception>

int main() {
    try {
        Game::MyApplication application;
        application.run();
    } catch (const Blueprint::Core::Exception& exception) {
        exception.log();
        return EXIT_FAILURE;
    } catch (const std::exception& exception) {
        const Blueprint::Core::Exception bpException(exception);
        bpException.log();
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
