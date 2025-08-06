#ifndef PLATFORMER_CORE_SAVER_HPP
#define PLATFORMER_CORE_SAVER_HPP

#include <nlohmann/json.hpp>
#include <SFML/System/Vector2.hpp>

namespace Platformer {
class Saver {
public:
    template<class T>
    static void saveVector2(nlohmann::ordered_json& data, const sf::Vector2<T>& vector, const char* key);
    static void saveVector2i(nlohmann::ordered_json& data, const sf::Vector2i& vector, const char* key);
    static void saveVector2f(nlohmann::ordered_json& data, const sf::Vector2f& vector, const char* key);
    static void saveVector2u(nlohmann::ordered_json& data, const sf::Vector2u& vector, const char* key);
};
} // Platformer

template<class T>
void Platformer::Saver::saveVector2(nlohmann::ordered_json& data, const sf::Vector2<T>& vector, const char* key) {
    data[key] = {{"X", vector.x}, {"Y", vector.y}};
}

#endif // PLATFORMER_CORE_SAVER_HPP
