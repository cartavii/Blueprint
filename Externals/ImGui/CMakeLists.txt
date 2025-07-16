cmake_minimum_required(VERSION 3.28)
project(ImGui LANGUAGES CXX)

file(GLOB IMGUI_SOURCES "Source/*.cpp")
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC "Include")
