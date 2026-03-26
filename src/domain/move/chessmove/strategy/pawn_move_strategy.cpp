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
                moves.push_back(std::make_shared<ChessMove>(from, oneStepForward));
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
                    from, twoStepsForward));
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
                        from, captureLeft));
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
                        from, captureRight));
                }
            }
        }

        // en passant links
        boardgame::core::Position enPassantLeft{
            from.row,
            from.col - 1
        };

        if (board.isInside(enPassantLeft))
        {
            auto target = board.getPieceAt(enPassantLeft);

            if (target &&
                target->getColor() != piece.getColor() &&
                target->getType() == boardgame::piece::chess::ChessPieceType::Pawn)
            {
                boardgame::core::Position to{
                    from.row + direction,
                    from.col - 1
                };

                moves.push_back(std::make_shared<ChessMove>(
                    from, to, ChessMoveType::EnPassant));
            }
        }

        // en passant rechts
        boardgame::core::Position enPassantRight{
            from.row,
            from.col + 1
        };

        if (board.isInside(enPassantRight))
        {
            auto target = board.getPieceAt(enPassantRight);

            if (target &&
                target->getColor() != piece.getColor() &&
                target->getType() == boardgame::piece::chess::ChessPieceType::Pawn)
            {
                boardgame::core::Position to{
                    from.row + direction,
                    from.col + 1
                };

                moves.push_back(std::make_shared<ChessMove>(
                    from, to, ChessMoveType::EnPassant));
            }
        }

        return moves;
    }
}