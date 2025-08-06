cmake_minimum_required(VERSION 3.28)
project(PlatformerGame LANGUAGES CXX)

file(GLOB_RECURSE PLATFORMER_GAME_SOURCES "Source/*.cpp")
add_executable(PlatformerGame ${PLATFORMER_GAME_SOURCES})
target_compile_features(PlatformerGame PRIVATE cxx_std_17)

target_include_directories(PlatformerGame PRIVATE "Include")
target_link_libraries(PlatformerGame PRIVATE PlatformerCore)
target_link_libraries(PlatformerGame PRIVATE Blueprint::Game)

copy_resources(PlatformerGame)
