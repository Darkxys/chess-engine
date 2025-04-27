cmake_minimum_required(VERSION 3.15)
project(models)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 REQUIRED)

pybind11_add_module(models
	wrapper.cpp
)

target_link_libraries(models PRIVATE EngineCore)
target_include_directories(models PRIVATE	
	${CMAKE_SOURCE_DIR}/engine-core/include
)