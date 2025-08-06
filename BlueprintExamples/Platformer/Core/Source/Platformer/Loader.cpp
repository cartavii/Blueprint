#include "Platformer/Loader.hpp"

sf::Vector2i Platformer::Loader::loadVector2i(const nlohmann::ordered_json& data, const char* key) {
    return loadVector2<int>(data, key);
}

sf::Vector2f Platformer::Loader::loadVector2f(const nlohmann::ordered_json& data, const char* key) {
    return loadVector2<float>(data, key);
}

sf::Vector2u Platformer::Loader::loadVector2u(const nlohmann::ordered_json& data, const char* key) {
    return loadVector2<unsigned int>(data, key);
}

sf::Vector2i Platformer::Loader::loadVector2i(const nlohmann::ordered_json& vectorData) {
    return loadVector2<int>(vectorData);
}

sf::Vector2f Platformer::Loader::loadVector2f(const nlohmann::ordered_json& vectorData) {
    return loadVector2<float>(vectorData);
}

sf::Vector2u Platformer::Loader::loadVector2u(const nlohmann::ordered_json& vectorData) {
    return loadVector2<unsigned int>(vectorData);
}
