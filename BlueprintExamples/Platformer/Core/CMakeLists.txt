cmake_minimum_required(VERSION 3.28)
project(PlatformerCore LANGUAGES CXX)

file(GLOB_RECURSE PLATFORMER_CORE_SOURCES "Source/*.cpp")
add_library(PlatformerCore STATIC ${PLATFORMER_CORE_SOURCES})
target_compile_features(PlatformerCore PRIVATE cxx_std_17)

target_include_directories(PlatformerCore PUBLIC "Include")
target_link_libraries(PlatformerCore PUBLIC nlohmann::json)
target_link_libraries(PlatformerCore PUBLIC Blueprint::Resources)

copy_resources(PlatformerCore)
