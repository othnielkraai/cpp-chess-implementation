#include "domain/move/chessmove/strategy/rook_move_strategy.hpp"

#include <array>

#include "core/common/position.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/IChessPiece.hpp"

// vervang dit door jouw concrete move class
#include "domain/move/chessmove/chess_move.hpp"

namespace boardgame::move::chess
{
    std::vector<std::shared_ptr<IChessMove>> RookMoveStrategy::generateMoves(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& from
    ) const
    {
        static constexpr std::array<std::pair<int, int>, 4> directions{{
            {-1,  0}, // omhoog
            { 1,  0}, // omlaag
            { 0, -1}, // links
            { 0,  1}  // rechts
        }};

        std::vector<std::shared_ptr<IChessMove>> moves;

        for (const auto& [rowStep, colStep] : directions)
        {
            boardgame::core::Position current = from;

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
                        std::make_shared<ChessMove>(from, current)
                    );
                    continue;
                }

                if (targetPiece->getColor() != piece.getColor())
                {
                    moves.push_back(
                        std::make_shared<ChessMove>(from, current)
                    );
                }

                break;
            }
        }

        return moves;
    }
}