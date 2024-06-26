cmake_minimum_required(VERSION 3.20)

project(drawing)

set(FILES
    entity.hpp
    entity.cpp
    scene_node.hpp
    scene_node.cpp
    aircraft.hpp
    aircraft.cpp
    sprite_node.hpp
    sprite_node.cpp
    world.hpp
    world.cpp
    player_contoller.hpp
    player_contoller.cpp
    entity_commands.hpp
    entity_commands.cpp
    state_stack.hpp
    state_stack.cpp
    state.hpp
    state.cpp
    application.hpp
    application.cpp
    game_state.hpp
    game_state.cpp
    title_state.hpp
    title_state.cpp
    context.hpp
    menu_state.hpp
    menu_state.cpp
    pause_state.hpp
    pause_state.cpp
    loading_state.hpp
    loading_state.cpp)

add_library(drawing STATIC ${FILES})


target_include_directories(drawing PUBLIC ${CMAKE_SOURCE_DIR}/utility PUBLIC ${CMAKE_SOURCE_DIR}/command)
target_link_libraries(drawing INTERFACE utility PUBLIC command)
