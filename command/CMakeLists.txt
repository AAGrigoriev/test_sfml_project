cmake_minimum_required(VERSION 3.20)

project(sfml LANGUAGES CXX)

set(FILES
    command.hpp
    command.cpp
    command_category.hpp
    command_category.cpp
    command_queue.hpp
    command_queue.cpp)

add_library(command STATIC ${FILES})

target_link_libraries(command INTERFACE utility)
target_include_directories(command PUBLIC ${CMAKE_SOURCE_DIR}/utility)
