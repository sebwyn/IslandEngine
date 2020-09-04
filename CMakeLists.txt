cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(IslandEngine VERSION 0.1)

#TODO: add cmake for increasing compiler optimization level for release builds
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external)
add_subdirectory(src)
