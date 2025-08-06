#include "Platformer/Saver.hpp"

void Platformer::Saver::saveVector2i(nlohmann::ordered_json& data, const sf::Vector2i& vector, const char* key) {
    return saveVector2<int>(data, vector, key);
}

void Platformer::Saver::saveVector2f(nlohmann::ordered_json& data, const sf::Vector2f& vector, const char* key) {
    return saveVector2<float>(data, vector, key);
}

void Platformer::Saver::saveVector2u(nlohmann::ordered_json& data, const sf::Vector2u& vector, const char* key) {
    return saveVector2<unsigned int>(data, vector, key);
}
