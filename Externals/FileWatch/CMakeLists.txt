cmake_minimum_required(VERSION 3.28)
project(FileWatch LANGUAGES CXX)

add_library(FileWatch INTERFACE)
target_include_directories(FileWatch INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
)

add_library(filewatch ALIAS FileWatch)
