cmake_minimum_required(VERSION 3.15)
project(Models)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 REQUIRED)

pybind11_add_module(Models
	Wrapper.cpp
)

target_link_libraries(Models PRIVATE EngineCore)
target_include_directories(Models PRIVATE	
	${CMAKE_SOURCE_DIR}/EngineCore.Test/include
)