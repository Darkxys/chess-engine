#pragma once
#include <string>
#include "Pieces.hpp"
#include "State.hpp"
#include "Color.hpp"
#include "chess/Bitboard.hpp"
#include "chess/ChessMove.hpp"

struct ChessState : State<ChessState, ChessMove>
{
	static const int c_PIECES_AMOUNT = 12;

	ChessState() : ChessState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -") {};
	ChessState(std::string fen);

	void displayState();
	std::string toFEN();
	U64* getOccupancyBoards();

	Bitboard getBishopAttacks(int square, U64 occupancy);
	Bitboard getRookAttacks(int square, U64 occupancy);
	Bitboard getQueenAttacks(int square, U64 occupancy);
	Bitboard getNonSlidingPieceAttacks(Pieces piece, int square);

	std::vector<ChessMove> generateLegalMoves();
	std::unique_ptr<ChessState> getNextState(ChessMove m);

private:
	static bool isAttacksInitialized;
	Bitboard bitboards[c_PIECES_AMOUNT];
	U64 occupancies_[3];
	Color side_;		// Current player playing
	int castle_;		// Castle rights
	int enpassant_;	// Enpassant square

	// Private constructor from a ChessState

	// Init sliders attack masks
	static Bitboard s_ROOK_MASKS[64];
	static Bitboard s_BISHOP_MASKS[64];

	// Init sliders attacks
	static Bitboard s_ROOK_ATTACKS[64][4096];
	static Bitboard s_BISHOP_ATTACKS[64][512];

	void initializeSliderAttacks();
	void initializeNonSliderAttacks();

	bool isSquareAttacked(int square, Color side);

	Bitboard generateBishopAttackMask(int square);
	Bitboard generateRookAttackMask(int square);

	void generateOccupancyBoards();
	Bitboard getBishopAttacksSlow(int square, Bitboard blockers);
	Bitboard getRookAttacksSlow(int square, Bitboard blockers);
	Bitboard setOccupancy(int index, int bitsInMask, Bitboard attackMask);

	std::unique_ptr<ChessState> makeMove(ChessMove m);
	std::vector<ChessMove> generateAllMoves();
};

