#include "chess-bitboard/chess_move.hpp"

ChessMove::ChessMove(int source, int target, int piece, int promotion, bool capture, bool doublePush, bool enpassant, bool castling)
{
	this->source_ = source;
	this->target_ = target;
	this->piece_ = piece;
	this->promotion_ = promotion;
	this->capture_ = capture;
	this->doublePush_ = doublePush;
	this->enpassant_ = enpassant;
	this->castling_ = castling;
}

uint8_t ChessMove::source()
{
	return this->source_;
}

uint8_t ChessMove::target()
{
	return this->target_;
}

uint8_t ChessMove::piece()
{
	return this->piece_;
}

uint8_t ChessMove::promotion()
{
	return this->promotion_;
}

bool ChessMove::capture()
{
	return this->capture_;
}

bool ChessMove::doublePush()
{
	return this->doublePush_;
}

bool ChessMove::enpassant()
{
	return this->enpassant_;
}

bool ChessMove::castling()
{
	return this->castling_;
}
