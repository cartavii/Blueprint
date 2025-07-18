cmake_minimum_required(VERSION 3.28)
project(Editor LANGUAGES CXX)

file(GLOB_RECURSE EDITOR_SOURCES "Source/*.cpp")
add_executable(Editor ${EDITOR_SOURCES})
target_compile_features(Editor PRIVATE cxx_std_17)

target_include_directories(Editor PRIVATE "Include")
target_link_libraries(Editor PRIVATE Blueprint::Editor)
