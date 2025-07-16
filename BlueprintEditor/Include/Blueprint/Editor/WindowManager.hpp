#ifndef BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
#define BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP

namespace Blueprint::Editor {
class Application;
class WindowManager {
public:
    explicit WindowManager(Application& application);
    ~WindowManager() = default;

public:
    void gui();

    [[nodiscard]] Application& getApplication();
    [[nodiscard]] const Application& getApplication() const;

private:
    Application& m_Application;
};
} // Blueprint::Editor

#endif // BLUEPRINT_EDITOR_WINDOW_MANAGER_HPP
