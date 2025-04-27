cmake_minimum_required(VERSION 3.15)
project(unit-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UnitTests
    main.cpp
)

target_link_libraries(UnitTests PRIVATE EngineCore)
target_include_directories(UnitTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine-core/include
)
# Register a test for CTest
# add_test(NAME Perft COMMAND UnitTests)