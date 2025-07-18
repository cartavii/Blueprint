#include "Blueprint/Editor/Window.hpp"

#include <imgui.h>

Blueprint::Editor::Window::Window(WindowManager& manager, const std::string& title, const bool isOpen, const int flags)
: m_Manager(manager)
, m_Title(title)
, m_IsOpen(isOpen)
, m_Flags(flags) {}

void Blueprint::Editor::Window::show() {
    if (ImGui::Begin(m_Title.c_str(), &m_IsOpen, m_Flags)) {
        gui();
    }
    ImGui::End();
}

void Blueprint::Editor::Window::setOpenState(const bool isOpen) {
    m_IsOpen = isOpen;
}

void Blueprint::Editor::Window::open() {
    m_IsOpen = true;
}

void Blueprint::Editor::Window::close() {
    m_IsOpen = false;
}

void Blueprint::Editor::Window::setFlags(const int flags) {
    m_Flags = flags;
}

void Blueprint::Editor::Window::includeFlag(const int flag) {
    m_Flags |= flag;
}

void Blueprint::Editor::Window::excludeFlag(const int flag) {
    m_Flags &= ~flag;
}

Blueprint::Editor::WindowManager& Blueprint::Editor::Window::getWindowManager() {
    return m_Manager;
}

const Blueprint::Editor::WindowManager& Blueprint::Editor::Window::getWindowManager() const {
    return m_Manager;
}

const std::string& Blueprint::Editor::Window::getTitle() const {
    return m_Title;
}

bool Blueprint::Editor::Window::isOpen() const {
    return m_IsOpen;
}

int Blueprint::Editor::Window::getFlags() const {
    return m_Flags;
}
