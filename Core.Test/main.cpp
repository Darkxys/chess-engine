#include <iostream>
#include <vector>
#include <map>
#include "chess/ChessGame.hpp"

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
		std::cout << perft(i, std::unique_ptr<ChessState>(new ChessState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "))) << std::endl;
	return 0;
}
