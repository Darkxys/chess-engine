#include "chess-bitboard/chess_game.hpp"

std::unique_ptr<ChessState> ChessGame::nextState(ChessState s, ChessMove m)
{
    return s.getNextState(m);
}

std::vector<ChessMove> ChessGame::getLegalMoves(ChessState s)
{
    return s.generateLegalMoves();
}

std::unique_ptr<ChessState> ChessGame::getStartingState()
{
    return std::unique_ptr<ChessState>(new ChessState());
}

bool ChessGame::isGameEnded(ChessState s)
{
    return false;
}

float ChessGame::getGameReward(ChessState s)
{
    return 0.0f;
}
