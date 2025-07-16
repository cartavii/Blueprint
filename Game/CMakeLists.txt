cmake_minimum_required(VERSION 3.28)
project(Game LANGUAGES CXX)

file(GLOB_RECURSE GAME_SOURCES "Source/*.cpp")
add_executable(Game ${GAME_SOURCES})
target_compile_features(Game PRIVATE cxx_std_17)

target_include_directories(Game PRIVATE "Include")
target_link_libraries(Game PRIVATE Blueprint::Game)
