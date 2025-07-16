cmake_minimum_required(VERSION 3.28)
project(JSON LANGUAGES CXX)

add_library(JSON INTERFACE)
target_include_directories(JSON INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
)

add_library(nlohmann::json ALIAS JSON)
