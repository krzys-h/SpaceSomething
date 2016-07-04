cmake_minimum_required(VERSION 3.5)
project(SpaceSomething)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SFML 2.3.2 REQUIRED system window graphics audio)
find_package(SFGUI 0.3.0 REQUIRED)

add_definitions(-std=c++11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(data)
