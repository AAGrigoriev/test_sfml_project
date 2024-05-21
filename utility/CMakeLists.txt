cmake_minimum_required(VERSION 3.20)

project(utility)

set(FILES resource_holder.hpp resource_identifiers.hpp utility.hpp)

add_library(utility INTERFACE ${FILES})
