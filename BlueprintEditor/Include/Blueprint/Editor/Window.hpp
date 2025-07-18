#ifndef BLUEPRINT_EDITOR_WINDOW_HPP
#define BLUEPRINT_EDITOR_WINDOW_HPP

#include <string>

namespace Blueprint::Editor {
class WindowManager;
class Window {
public:
    Window(WindowManager& manager, const std::string& title, bool isOpen = false, int flags = 0);
    virtual ~Window() = default;

public:
    void show();

    void setOpenState(bool isOpen);
    void open();
    void close();

    void setFlags(int flags);
    void includeFlag(int flag);
    void excludeFlag(int flag);

    [[nodiscard]] WindowManager& getWindowManager();
    [[nodiscard]] const WindowManager& getWindowManager() const;

    [[nodiscard]] const std::string& getTitle() const;

    [[nodiscard]] bool isOpen() const;

    [[nodiscard]] int getFlags() const;

protected:
    virtual void gui() = 0;

private:
    WindowManager& m_Manager;
    std::string m_Title;
    bool m_IsOpen;
    bool m_Flags;
};
} // Blueprint::Editor::Gui

#endif // BLUEPRINT_EDITOR_WINDOW_HPP
