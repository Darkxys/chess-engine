cmake_minimum_required(VERSION 3.15)
project(engine-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(EngineCore STATIC
	
	src/point.cpp
	
	src/chess-bitboard/bitboard.cpp
	src/chess-bitboard/chess_game.cpp
	src/chess-bitboard/chess_move.cpp
	src/chess-bitboard/chess_state.cpp
 )

target_include_directories(EngineCore PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include
)