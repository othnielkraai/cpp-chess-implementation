#include "domain/move/chessmove/strategy/bishop_move_strategy.hpp"

namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> BishopMoveStrategy::generateMoves(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& from
    ) const
    {
        std::vector<std::unique_ptr<IChessMove>> moves;

        const int directions[4][2] = {
            {-1, -1},
            {-1,  1},
            { 1, -1},
            { 1,  1}
        };

        for (const auto& direction : directions)
        {
            int row = from.row + direction[0];
            int col = from.col + direction[1];

            while (board.isInside({row, col}))
            {
                boardgame::core::Position to{row, col};
                if (!board.getPieceAt(to))
                {
                    moves.push_back(std::make_unique<ChessMove>(from, to));
                }
                else
                {
                    const auto targetPiece = board.getPieceAt(to);

                    if (targetPiece->getColor() != piece.getColor())
                    {
                        moves.push_back(std::make_unique<ChessMove>(from, to));
                    }

                    break;
                }

                row += direction[0];
                col += direction[1];
            }
        }

        return moves;
    }

    std::unique_ptr<IChessMoveStrategy> BishopMoveStrategy::clone() const
    {
        return std::make_unique<BishopMoveStrategy>(*this);
    }
}