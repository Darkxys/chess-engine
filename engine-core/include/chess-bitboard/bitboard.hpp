#pragma once
#include <iostream>

#define U64 unsigned long long

class Bitboard
{
private:
	U64 board_;
public:
	Bitboard() : Bitboard(0ULL) {};
	Bitboard(U64 board);

	bool getBit(int index);
	void setBit(int index);
	void disableBit(int index);
	int countBits();
	U64 getBoard();
	int popLsb();
	int getLsb();
	int numberLeadingZero();

	void displayBoard();
};

