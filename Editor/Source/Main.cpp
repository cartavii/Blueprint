#include "Blueprint/Editor/Application.hpp"
#include "Blueprint/Core/Exception.hpp"

#include <exception>

int main() {
    try {
        Blueprint::Editor::Application application("Editor");
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
