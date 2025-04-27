#pragma once
#include <map>
#include <string>
#include "game.hpp"
#include "point.hpp"
#include "color.hpp"
#include "chess-bitboard/chess_move.hpp"
#include "chess-bitboard/chess_state.hpp"

class ChessGame : Game<ChessState, ChessMove>
{
private:
	std::map<std::string, unsigned int> stateHistory_;
public:
	std::unique_ptr<ChessState> nextState(ChessState s, ChessMove m);
	std::vector<ChessMove> getLegalMoves(ChessState s);
	std::unique_ptr<ChessState> getStartingState();
	bool isGameEnded(ChessState s);
	float getGameReward(ChessState s);
};

