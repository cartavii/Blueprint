cmake_minimum_required(VERSION 3.28)
project(BlueprintGame LANGUAGES CXX)

file(GLOB_RECURSE BLUEPRINT_GAME_SOURCES "Source/*.cpp")
add_library(BlueprintGame STATIC ${BLUEPRINT_GAME_SOURCES})
target_compile_features(BlueprintGame PRIVATE cxx_std_17)

target_include_directories(BlueprintGame PUBLIC "Include")
target_link_libraries(BlueprintGame PUBLIC nlohmann::json)
target_link_libraries(BlueprintGame PUBLIC Blueprint::Resources)

add_library(Blueprint::Game ALIAS BlueprintGame)
