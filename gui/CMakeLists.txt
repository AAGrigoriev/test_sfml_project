cmake_minimum_required(VERSION 3.20)

project(gui)

add_library(gui STATIC
    component.hpp
    component.cpp
    container.cpp
    container.hpp
    label.hpp
    label.cpp
    button.cpp
    button.hpp
)

target_include_directories(gui PRIVATE ${CMAKE_SOURCE_DIR}/utility)

target_link_libraries(gui PRIVATE utility)
