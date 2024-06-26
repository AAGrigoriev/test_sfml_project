cmake_minimum_required(VERSION 3.20)

if($ENV{GITHUB_RUN_NUMBER})
  set(VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
  set(VERSION 0.0.0)
endif()

project(sfml LANGUAGES CXX VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfml main.cpp)

add_subdirectory(drawing)
add_subdirectory(utility)
add_subdirectory(command)

find_package(SFML
    COMPONENTS
    system window graphics network audio REQUIRED)

target_link_libraries(sfml
    PUBLIC sfml-graphics
    PRIVATE drawing)
