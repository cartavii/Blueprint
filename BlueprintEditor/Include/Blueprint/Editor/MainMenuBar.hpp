#ifndef BLUEPRINT_EDITOR_MAIN_MENU_BAR_HPP
#define BLUEPRINT_EDITOR_MAIN_MENU_BAR_HPP

namespace Blueprint::Editor {
class Application;
class MainMenuBar {
public:
    explicit MainMenuBar(Application& application);

public:
    void gui();

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

private:
    Application& m_Application;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_MAIN_MENU_BAR_HPP
