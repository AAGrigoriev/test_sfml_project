cmake_minimum_required(VERSION 3.20)

project(drawing)

set(FILES
    entity.hpp
    entity.cpp
    scene_node.hpp
    scene_node.cpp
    aircraft.hpp
    aircraft.cpp)

add_library(drawing STATIC ${FILES}
    sprite_node.hpp
    sprite_node.cpp
    world.hpp
    world.cpp
)
target_include_directories(drawing PUBLIC ${CMAKE_SOURCE_DIR}/resource_holder)
target_link_libraries(drawing INTERFACE resource_holder)
