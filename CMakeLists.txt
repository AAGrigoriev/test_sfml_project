cmake_minimum_required(VERSION 3.5)

project(sfml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfml main.cpp
    game.hpp
    game.cpp
    resource_holder.hpp)

find_package(SFML
  COMPONENTS
    system window graphics network audio REQUIRED)

target_link_libraries(sfml sfml-graphics)
