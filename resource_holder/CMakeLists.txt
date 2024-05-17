cmake_minimum_required(VERSION 3.20)

project(resource_holder)

set(FILES resource_holder.hpp resource_identifiers.hpp)

add_library(resource_holder INTERFACE ${FILES})
target_include_directories(resource_holder INTERFACE .)
