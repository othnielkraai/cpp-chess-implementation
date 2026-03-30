#include "domain/move/chessmove/strategy/knight_move_strategy.hpp"



namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> KnightMoveStrategy::generateMoves(
        const IChessBoard& board,
        const IChessPiece& piece,
        const Position& from
    ) const
    {
        static constexpr std::array<std::pair<int, int>, 8> offsets{{
            {-2, -1}, {-2,  1},
            {-1, -2}, {-1,  2},
            { 1, -2}, { 1,  2},
            { 2, -1}, { 2,  1}
        }};

        std::vector<std::unique_ptr<IChessMove>> moves;

        for (const auto& [rowOffset, colOffset] : offsets)
        {
            boardgame::core::Position to{
                from.row + rowOffset,
                from.col + colOffset
            };

            if (!board.isInside(to))
            {
                continue;
            }

            auto targetPiece = board.getPieceAt(to);

            if (!targetPiece)
            {
                moves.push_back(std::make_unique<ChessMove>(from, to));
                continue;
            }

            if (targetPiece->getColor() != piece.getColor())
            {

                moves.push_back(std::make_unique<ChessMove>(from, to));
            }
        }

        return moves;
    }
}