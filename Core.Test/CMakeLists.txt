cmake_minimum_required(VERSION 3.15)
project(Core.Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Core.Test
    main.cpp
)

target_link_libraries(Core.Test PRIVATE Core)
target_include_directories(Core.Test PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/include
)
# Register a test for CTest
# add_test(NAME Perft COMMAND UnitTests)