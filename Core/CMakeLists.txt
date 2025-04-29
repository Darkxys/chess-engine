cmake_minimum_required(VERSION 3.15)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(Core STATIC
	
	src/Point.cpp
	
	src/chess/Bitboard.cpp
	src/chess/ChessGame.cpp
	src/chess/ChessMove.cpp
	src/chess/ChessState.cpp
 )

target_include_directories(Core PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)