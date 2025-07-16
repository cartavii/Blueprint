#ifndef BLUEPRINT_EDITOR_GUI_API_HPP
#define BLUEPRINT_EDITOR_GUI_API_HPP

#include "Blueprint/Core/Exception.hpp"

#include <SFML/System/Clock.hpp>

namespace sf {
class RenderWindow;
class Event;
} // sf

namespace Blueprint::Editor {
class GuiApiInitFail final : public Core::Exception {
public:
    GuiApiInitFail();
};

class GuiApi {
public:
    explicit GuiApi(sf::RenderWindow& renderWindow);
    ~GuiApi();

public:
    void processEvent(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow& m_RenderWindow;
    sf::Clock m_DeltaClock;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_GUI_API_HPP
