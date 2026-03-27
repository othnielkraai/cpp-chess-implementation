#include "domain/move/chessmove/strategy/knight_move_strategy.hpp"

#include <array>

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "domain/move/chessmove/chess_move.hpp"

namespace boardgame::move::chess
{
    std::vector<std::shared_ptr<IChessMove>> KnightMoveStrategy::generateMoves(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& from
    ) const
    {
        static constexpr std::array<std::pair<int, int>, 8> offsets{{
            {-2, -1}, {-2,  1},
            {-1, -2}, {-1,  2},
            { 1, -2}, { 1,  2},
            { 2, -1}, { 2,  1}
        }};

        std::vector<std::shared_ptr<IChessMove>> moves;

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
                moves.push_back(std::make_shared<ChessMove>(from, to));
                continue;
            }

            if (targetPiece->getColor() != piece.getColor())
            {

                moves.push_back(std::make_shared<ChessMove>(from, to));
            }
        }

        return moves;
    }
}