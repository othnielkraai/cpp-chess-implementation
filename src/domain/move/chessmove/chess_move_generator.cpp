#include "domain/move/chessmove/chess_move_generator.hpp"

namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> ChessMoveGenerator::generateMoves(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::piece::chess::IChessPiece &piece,
        const boardgame::core::Position &from) const
    {
        return piece.getMoveStrategy().generateMoves(board, piece, from);
    }
}