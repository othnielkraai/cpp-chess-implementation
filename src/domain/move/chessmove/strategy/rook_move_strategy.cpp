#include "domain/move/chessmove/strategy/rook_move_strategy.hpp"


namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> RookMoveStrategy::generateMoves(
        const IChessBoard& board,
        const IChessPiece& piece,
        const Position& from
    ) const
    {
        static constexpr std::array<std::pair<int, int>, 4> directions{{
            {-1,  0}, // up
            { 1,  0}, // down
            { 0, -1}, // left
            { 0,  1}  // right
        }};

        std::vector<std::unique_ptr<IChessMove>> moves;

        for (const auto& [rowStep, colStep] : directions)
        {
            Position current = from;

            while (true)
            {
                current.row += rowStep;
                current.col += colStep;

                if (!board.isInside(current))
                {
                    break;
                }

                auto targetPiece = board.getPieceAt(current);

                if (!targetPiece)
                {
                    moves.push_back(
                        std::make_unique<ChessMove>(from, current)
                    );
                    continue;
                }

                if (targetPiece->getColor() != piece.getColor())
                {
                    moves.push_back(
                        std::make_unique<ChessMove>(from, current)
                    );
                }

                break;
            }
        }

        return moves;
    }

    std::unique_ptr<IChessMoveStrategy> RookMoveStrategy::clone() const
    {
        return std::make_unique<RookMoveStrategy>(*this);
    }
}