cmake_minimum_required(VERSION 3.28)
project(ImGuiSFML LANGUAGES CXX)

file(GLOB IMGUI_SFML_SOURCES "Source/*.cpp")
add_library(ImGuiSFML STATIC ${IMGUI_SFML_SOURCES})
target_include_directories(ImGuiSFML PUBLIC "Include")
target_link_libraries(ImGuiSFML PUBLIC SFML::Graphics)
target_link_libraries(ImGuiSFML PUBLIC ImGui)

add_library(ImGui::SFML ALIAS ImGuiSFML)
