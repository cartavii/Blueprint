cmake_minimum_required(VERSION 3.28)
project(Blueprint LANGUAGES CXX)

add_subdirectory("Externals/FileWatch")
add_subdirectory("Externals/JSON")
add_subdirectory("Externals/SFML")
add_subdirectory("Externals/ImGui")
add_subdirectory("Externals/ImGuiSFML")

add_subdirectory("BlueprintCore")
add_subdirectory("BlueprintResources")
add_subdirectory("BlueprintEditor")
add_subdirectory("BlueprintGame")

add_subdirectory("BlueprintExamples" EXCLUDE_FROM_ALL)
