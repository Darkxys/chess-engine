#include <iostream>
#include <vector>
#include <map>
#include "chess-bitboard/chess_game.hpp"

ChessGame game = ChessGame();

std::map<ChessState,ChessMove> movesPromote = std::map<ChessState,ChessMove>();

unsigned long long perft(int depth, std::unique_ptr<ChessState> state) {
	if (depth == 0) {
		return 1;
	}

	std::vector<ChessMove> moveList = game.getLegalMoves(*state);
	unsigned long long counter = 0;

	for (ChessMove move : moveList) {
		counter += perft(depth - 1, game.nextState(*state, move));
	}

	return counter;
}

int main() {
	for(int i = 1; i <= 5; i++)
		std::cout << perft(i, std::unique_ptr<ChessState>(new ChessState("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"))) << std::endl;
	return 0;
}
