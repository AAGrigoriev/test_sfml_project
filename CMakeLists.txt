cmake_minimum_required(VERSION 3.20)

project(sfml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfml main.cpp
    game.hpp
    game.cpp)

add_subdirectory(drawing)
add_subdirectory(resource_holder)

find_package(SFML
    COMPONENTS
    system window graphics network audio REQUIRED)

target_link_libraries(sfml PUBLIC drawing INTERFACE resource_holder PUBLIC sfml-graphics)
