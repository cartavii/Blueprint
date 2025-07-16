cmake_minimum_required(VERSION 3.28)
project(BlueprintEditor LANGUAGES CXX)

file(GLOB_RECURSE BLUEPRINT_EDITOR_SOURCES "Source/*.cpp")
add_library(BlueprintEditor STATIC ${BLUEPRINT_EDITOR_SOURCES})
target_compile_features(BlueprintEditor PRIVATE cxx_std_17)

target_include_directories(BlueprintEditor PUBLIC "Include")
target_link_libraries(BlueprintEditor PUBLIC nlohmann::json)
target_link_libraries(BlueprintEditor PUBLIC filewatch)
target_link_libraries(BlueprintEditor PUBLIC Blueprint::Resources)

add_library(Blueprint::Editor ALIAS BlueprintEditor)
