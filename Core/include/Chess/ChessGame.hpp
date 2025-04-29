#pragma once
#include <map>
#include <string>
#include "Game.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "chess/ChessMove.hpp"
#include "chess/ChessState.hpp"

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

