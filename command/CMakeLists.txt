cmake_minimum_required(VERSION 3.20)

project(sfml LANGUAGES CXX)

set(FILES
    command.hpp
    command.cpp
    category_command.hpp
    command_queue.hpp
    command_queue.cpp

)

add_library(command STATIC ${FILES})

target_link_libraries(command INTERFACE utility)
target_include_directories(command PRIVATE ${CMAKE_SOURCE_DIR}/utility)
