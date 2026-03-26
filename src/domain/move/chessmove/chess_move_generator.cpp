#include "domain/move/chessmove/chess_move_generator.hpp"

namespace boardgame::move::chess
{
    std::vector<std::shared_ptr<IChessMove>> ChessMoveGenerator::generateMoves(
        const boardgame::board::chess::IChessBoard& board,
        boardgame::piece::chess::ChessPieceColor color
    ) const
    {
        std::vector<std::shared_ptr<IChessMove>> moves;

        auto pieces = board.getPieces(color);

        for (const auto& [pos, piece] : pieces)
        {
            auto pieceMoves = piece->getMoveStrategy().generateMoves(
                board,
                *piece,
                pos
            );

            moves.insert(
                moves.end(),
                pieceMoves.begin(),
                pieceMoves.end()
            );
        }

        return moves;
    }
}