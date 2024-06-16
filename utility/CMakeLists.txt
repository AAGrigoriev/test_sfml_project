cmake_minimum_required(VERSION 3.20)

project(utility)

set(FILES resource_holder.hpp resource_identifiers.hpp flags.hpp math.hpp math.cpp)

add_library(utility STATIC ${FILES})
