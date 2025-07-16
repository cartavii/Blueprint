#include "Blueprint/Editor/GuiApi.hpp"

#include <imgui-SFML.h>
#include <SFMl/Graphics/RenderWindow.hpp>

#include "imgui.h"

Blueprint::Editor::GuiApiInitFail::GuiApiInitFail()
: Exception("Failed to initialize Gui API") {}

Blueprint::Editor::GuiApi::GuiApi(sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow) {
    if (!ImGui::SFML::Init(m_RenderWindow)) {
        throw GuiApiInitFail();
    }
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

Blueprint::Editor::GuiApi::~GuiApi() {
    ImGui::SFML::Shutdown(m_RenderWindow);
}

void Blueprint::Editor::GuiApi::processEvent(const sf::Event& event) {
    ImGui::SFML::ProcessEvent(m_RenderWindow, event);
}

void Blueprint::Editor::GuiApi::update() {
    ImGui::SFML::Update(m_RenderWindow, m_DeltaClock.restart());
    ImGui::DockSpaceOverViewport();
}

void Blueprint::Editor::GuiApi::render() {
    ImGui::SFML::Render(m_RenderWindow);
}
