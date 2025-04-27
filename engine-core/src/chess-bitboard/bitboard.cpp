#include "chess-bitboard/bitboard.hpp"

Bitboard::Bitboard(U64 board)
{
	this->board_ = board;
}

bool Bitboard::getBit(int index)
{
	return (this->board_ & (1ULL << index));
}

void Bitboard::setBit(int index)
{
	(this->board_ |= (1ULL << index));
}

void Bitboard::disableBit(int index)
{
	(this->getBit(index) ? this->board_ ^= (1ULL << index) : 0);
}

int Bitboard::countBits()
{
	int count = 0;
	U64 bitboard = this->board_;

	while (bitboard) {
		count++;
		bitboard &= bitboard - 1;
	}

	return count;
}

U64 Bitboard::getBoard()
{
	return this->board_;
}

int Bitboard::popLsb()
{
	int lsbIndex = Bitboard((this->board_ & -static_cast<__int64>(this->board_)) - 1).countBits();
	this->board_ &= this->board_ - 1;
	return lsbIndex;
}

int Bitboard::getLsb()
{
	return Bitboard((this->board_ & -static_cast<__int64>(this->board_)) - 1).countBits();
}

int Bitboard::numberLeadingZero()
{
	U64 board = this->board_;
	U64 y;
	long n, c;
	n = 64;
	c = 32;
	do {
		y = board >> c;
		if (y != 0) {
			n = n - c;
			board = y;
		}
		c = c >> 1;
	} while (c != 0);
	return n - board;
}

void Bitboard::displayBoard()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			std::cout << this->getBit(row * 8 + col) ? 1 : 0;
		}
		std::cout << std::endl;
	}
}
