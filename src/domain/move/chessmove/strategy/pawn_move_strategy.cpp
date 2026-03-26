#include "domain/move/chessmove/strategy/pawn_move_strategy.hpp"

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "domain/move/chessmove/chess_move.hpp"

namespace boardgame::move::chess
{
    std::vector<std::shared_ptr<IChessMove>> PawnMoveStrategy::generateMoves(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& from
    ) const
    {
        std::vector<std::shared_ptr<IChessMove>> moves;

        const bool isWhite =
            piece.getColor() == boardgame::piece::chess::ChessPieceColor::White;

        const int direction = isWhite ? -1 : 1;
        const int startRow = isWhite ? 6 : 1;

        // 1 stap vooruit
        boardgame::core::Position oneStepForward{
            from.row + direction,
            from.col
        };

        if (board.isInside(oneStepForward) && !board.getPieceAt(oneStepForward))
        {
            moves.push_back(std::make_shared<ChessMove>(from, oneStepForward));

            // 2 stappen vooruit vanaf startpositie
            boardgame::core::Position twoStepsForward{
                from.row + (2 * direction),
                from.col
            };

            if (from.row == startRow &&
                board.isInside(twoStepsForward) &&
                !board.getPieceAt(twoStepsForward))
            {
                moves.push_back(std::make_shared<ChessMove>(from, twoStepsForward));
            }
        }

        // diagonaal links slaan
        boardgame::core::Position captureLeft{
            from.row + direction,
            from.col - 1
        };

        if (board.isInside(captureLeft))
        {
            auto targetPiece = board.getPieceAt(captureLeft);
            if (targetPiece && targetPiece->getColor() != piece.getColor())
            {
                moves.push_back(std::make_shared<ChessMove>(from, captureLeft));
            }
        }

        // diagonaal rechts slaan
        boardgame::core::Position captureRight{
            from.row + direction,
            from.col + 1
        };

        if (board.isInside(captureRight))
        {
            auto targetPiece = board.getPieceAt(captureRight);
            if (targetPiece && targetPiece->getColor() != piece.getColor())
            {
                moves.push_back(std::make_shared<ChessMove>(from, captureRight));
            }
        }

        return moves;
    }
}