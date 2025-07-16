cmake_minimum_required(VERSION 3.28)
project(BlueprintResources LANGUAGES CXX)

file(GLOB_RECURSE BLUEPRINT_RESOURCES_SOURCES "Source/*.cpp")
add_library(BlueprintResources STATIC ${BLUEPRINT_RESOURCES_SOURCES}
        Source/Blueprint/Resources/ResourceManager.cpp)
target_compile_features(BlueprintResources PRIVATE cxx_std_17)

target_include_directories(BlueprintResources PUBLIC "Include")
target_link_libraries(BlueprintResources PUBLIC Blueprint::Core)

add_custom_command(
        TARGET BlueprintResources POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "${CMAKE_BINARY_DIR}/Resources"
)

add_library(Blueprint::Resources ALIAS BlueprintResources)
