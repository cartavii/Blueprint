cmake_minimum_required(VERSION 3.28)
project(BlueprintCore LANGUAGES CXX)

file(GLOB_RECURSE BLUEPRINT_CORE_SOURCES "Source/*.cpp")
add_library(BlueprintCore STATIC ${BLUEPRINT_CORE_SOURCES})
target_compile_features(BlueprintCore PRIVATE cxx_std_17)

target_include_directories(BlueprintCore PUBLIC "Include")
target_link_libraries(BlueprintCore PUBLIC ImGui::SFML)

add_library(Blueprint::Core ALIAS BlueprintCore)
