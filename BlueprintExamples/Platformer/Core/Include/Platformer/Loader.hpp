#ifndef PLATFORMER_CORE_LOADER_HPP
#define PLATFORMER_CORE_LOADER_HPP

#include <nlohmann/json.hpp>
#include <SFML/System/Vector2.hpp>

namespace Platformer {
class Loader {
public:
    template<class T>
    static T loadValue(const nlohmann::ordered_json& data, const char* key);

    template<class T>
    static sf::Vector2<T> loadVector2(const nlohmann::ordered_json& data, const char* key);
    static sf::Vector2i loadVector2i(const nlohmann::ordered_json& data, const char* key);
    static sf::Vector2f loadVector2f(const nlohmann::ordered_json& data, const char* key);
    static sf::Vector2u loadVector2u(const nlohmann::ordered_json& data, const char* key);

    template<class T>
    static sf::Vector2<T> loadVector2(const nlohmann::ordered_json& vectorData);
    static sf::Vector2i loadVector2i(const nlohmann::ordered_json& vectorData);
    static sf::Vector2f loadVector2f(const nlohmann::ordered_json& vectorData);
    static sf::Vector2u loadVector2u(const nlohmann::ordered_json& vectorData);
};
} // Platformer

template<class T>
T Platformer::Loader::loadValue(const nlohmann::ordered_json& data, const char* key) {
    if (data.contains(key)) {
        return data[key].get<T>();
    }
    return {};
}

template<class T>
sf::Vector2<T> Platformer::Loader::loadVector2(const nlohmann::ordered_json& data, const char* key) {
    if (data.contains(key)) {
        return loadVector2<T>(data[key].get<nlohmann::ordered_json>());
    }
    return {};
}

template<class T>
sf::Vector2<T> Platformer::Loader::loadVector2(const nlohmann::ordered_json& vectorData) {
    return {loadValue<T>(vectorData, "X"), loadValue<T>(vectorData, "Y")};
}

#endif // PLATFORMER_CORE_LOADER_HPP
