cmake_minimum_required(VERSION 3.20)

project(gui)

add_library(gui STATIC  component.hpp container.cpp container.hpp)

target_include_directories(drawing PUBLIC ${CMAKE_SOURCE_DIR}/utility)
#target_link_libraries(drawing INTERFACE utility PUBLIC command)
