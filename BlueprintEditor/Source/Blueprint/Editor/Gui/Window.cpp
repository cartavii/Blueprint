#include "Blueprint/Editor/Gui/Window.hpp"

#include <imgui.h>

Blueprint::Editor::Gui::Window::Window(WindowManager& manager, const std::string& title, const bool isOpen, const int flags)
: m_Manager(manager)
, m_Title(title)
, m_IsOpen(isOpen)
, m_Flags(flags) {}

void Blueprint::Editor::Gui::Window::show() {
    if (ImGui::Begin(m_Title.c_str(), &m_IsOpen, m_Flags)) {
        guiRender();
    }
    ImGui::End();
}

void Blueprint::Editor::Gui::Window::setOpenState(const bool isOpen) {
    m_IsOpen = isOpen;
}

void Blueprint::Editor::Gui::Window::open() {
    m_IsOpen = true;
}

void Blueprint::Editor::Gui::Window::close() {
    m_IsOpen = false;
}

void Blueprint::Editor::Gui::Window::setFlags(const int flags) {
    m_Flags = flags;
}

void Blueprint::Editor::Gui::Window::includeFlag(const int flag) {
    m_Flags |= flag;
}

void Blueprint::Editor::Gui::Window::excludeFlag(const int flag) {
    m_Flags &= ~flag;
}

Blueprint::Editor::Gui::WindowManager& Blueprint::Editor::Gui::Window::getWindowManager() {
    return m_Manager;
}

const Blueprint::Editor::Gui::WindowManager& Blueprint::Editor::Gui::Window::getWindowManager() const {
    return m_Manager;
}

const std::string& Blueprint::Editor::Gui::Window::getTitle() const {
    return m_Title;
}

bool Blueprint::Editor::Gui::Window::isOpen() const {
    return m_IsOpen;
}

int Blueprint::Editor::Gui::Window::getFlags() const {
    return m_Flags;
}
