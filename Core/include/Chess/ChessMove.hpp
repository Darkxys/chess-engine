#pragma once
#include "Move.hpp"
#include <cstdint>

class ChessMove : Move<ChessMove>
{
private:
	// Properties
	uint8_t source_;
	uint8_t target_;
	uint8_t piece_;
	uint8_t promotion_;
	bool capture_;
	bool doublePush_;
	bool enpassant_;
	bool castling_;
public:

	// Constructor
	ChessMove() : ChessMove(0,0,0,0) {};
	ChessMove(int source, int target, int piece, int promotion, bool capture = false, bool doublePush = false, bool enpassant = false, bool castling = false);

	// Getters
	uint8_t source();
	uint8_t target();
	uint8_t piece();
	uint8_t promotion();
	bool capture();
	bool doublePush();
	bool enpassant();
	bool castling();
};

