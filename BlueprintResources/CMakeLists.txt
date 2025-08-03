cmake_minimum_required(VERSION 3.28)
project(BlueprintResources LANGUAGES CXX)

file(GLOB_RECURSE BLUEPRINT_RESOURCES_SOURCES "Source/*.cpp")
add_library(BlueprintResources STATIC ${BLUEPRINT_RESOURCES_SOURCES})
target_compile_features(BlueprintResources PRIVATE cxx_std_17)

target_include_directories(BlueprintResources PUBLIC "Include")
target_link_libraries(BlueprintResources PUBLIC Blueprint::Core)

function(copy_resources TARGET_NAME)
        add_custom_command(
                TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/../Resources"
                "${CMAKE_CURRENT_BINARY_DIR}/../Resources")
endfunction()

add_library(Blueprint::Resources ALIAS BlueprintResources)
