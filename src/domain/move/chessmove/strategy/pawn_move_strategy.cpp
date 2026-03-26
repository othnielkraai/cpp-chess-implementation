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
        const int promotionRow = isWhite ? 0 : 7;

        // 1 stap vooruit
        boardgame::core::Position oneStepForward{
            from.row + direction,
            from.col
        };

        if (board.isInside(oneStepForward) && !board.getPieceAt(oneStepForward))
        {
            if (oneStepForward.row == promotionRow)
            {
                moves.push_back(std::make_shared<ChessMove>(
                    from, oneStepForward, ChessMoveType::Promotion));
            }
            else
            {
                moves.push_back(std::make_shared<ChessMove>(
                    from, oneStepForward, ChessMoveType::Normal));
            }

            // 2 stappen vooruit
            boardgame::core::Position twoStepsForward{
                from.row + (2 * direction),
                from.col
            };

            if (from.row == startRow &&
                board.isInside(twoStepsForward) &&
                !board.getPieceAt(twoStepsForward))
            {
                moves.push_back(std::make_shared<ChessMove>(
                    from, twoStepsForward, ChessMoveType::PawnDoubleMove));
            }
        }

        // capture links
        boardgame::core::Position captureLeft{
            from.row + direction,
            from.col - 1
        };

        if (board.isInside(captureLeft))
        {
            auto targetPiece = board.getPieceAt(captureLeft);

            if (targetPiece && targetPiece->getColor() != piece.getColor())
            {
                if (captureLeft.row == promotionRow)
                {
                    moves.push_back(std::make_shared<ChessMove>(
                        from, captureLeft, ChessMoveType::Promotion));
                }
                else
                {
                    moves.push_back(std::make_shared<ChessMove>(
                        from, captureLeft, ChessMoveType::Normal));
                }
            }
        }

        // capture rechts
        boardgame::core::Position captureRight{
            from.row + direction,
            from.col + 1
        };

        if (board.isInside(captureRight))
        {
            auto targetPiece = board.getPieceAt(captureRight);

            if (targetPiece && targetPiece->getColor() != piece.getColor())
            {
                if (captureRight.row == promotionRow)
                {
                    moves.push_back(std::make_shared<ChessMove>(
                        from, captureRight, ChessMoveType::Promotion));
                }
                else
                {
                    moves.push_back(std::make_shared<ChessMove>(
                        from, captureRight, ChessMoveType::Normal));
                }
            }
        }

        // en passant
        const auto lastMove = board.lastMove();

        if (lastMove &&
            lastMove->getMoveType() == ChessMoveType::PawnDoubleMove)
        {
            const auto lastFrom = lastMove->getFrom();
            const auto lastTo = lastMove->getTo();

            // er moet een enemy pawn naast deze pawn geëindigd zijn
            if (lastTo.row == from.row &&
                (lastTo.col == from.col - 1 || lastTo.col == from.col + 1))
            {
                auto target = board.getPieceAt(lastTo);

                if (target &&
                    target->getType() == boardgame::piece::chess::ChessPieceType::Pawn &&
                    target->getColor() != piece.getColor())
                {
                    boardgame::core::Position enPassantTo{
                        from.row + direction,
                        lastTo.col
                    };

                    if (board.isInside(enPassantTo) && !board.getPieceAt(enPassantTo))
                    {
                        moves.push_back(std::make_shared<ChessMove>(
                            from, enPassantTo, ChessMoveType::EnPassant));
                    }
                }
            }
        }

        return moves;
    }
}