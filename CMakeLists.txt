cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0148 NEW)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Build the engine-core static library
add_subdirectory(Core)

# 2) Build and enable unit tests (perft)
enable_testing()
add_subdirectory(Core.Test)

# 3) Build Python models via pybind11
find_package(pybind11 REQUIRED)
add_subdirectory(Models)