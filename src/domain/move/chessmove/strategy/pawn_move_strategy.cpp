#include "domain/move/chessmove/strategy/pawn_move_strategy.hpp"


namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> PawnMoveStrategy::generateMoves(
        const IChessBoard& board,
        const IChessPiece& piece,
        const Position& from
    ) const
    {
        std::vector<std::unique_ptr<IChessMove>> moves;

        const bool isWhite = piece.getColor() == ChessPieceColor::White;

        const int direction = isWhite ? -1 : 1;
        const int startRow = isWhite ? 6 : 1;
        const int promotionRow = isWhite ? 0 : 7;

        Position oneStepForward{
            from.row + direction,
            from.col
        };

        if (board.isInside(oneStepForward) && !board.getPieceAt(oneStepForward))
        {
            if (oneStepForward.row == promotionRow)
            {
                moves.push_back(std::make_unique<IChessMove>(
                    from, oneStepForward, ChessMoveType::Promotion));
            }
            else
            {
                moves.push_back(std::make_unique<IChessMove>(
                    from, oneStepForward, ChessMoveType::Normal));
            }

            boardgame::core::Position twoStepsForward{
                from.row + (2 * direction),
                from.col
            };

            if (from.row == startRow &&
                board.isInside(twoStepsForward) &&
                !board.getPieceAt(twoStepsForward))
            {
                moves.push_back(std::make_unique<IChessMove>(
                    from, twoStepsForward, ChessMoveType::PawnDoubleMove));
            }
        }

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
                    moves.push_back(std::make_unique<IChessMove>(
                        from, captureLeft, ChessMoveType::Promotion));
                }
                else
                {
                    moves.push_back(std::make_unique<IChessMove>(
                        from, captureLeft, ChessMoveType::Normal));
                }
            }
        }

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
                    moves.push_back(std::make_unique<IChessMove>(
                        from, captureRight, ChessMoveType::Promotion));
                }
                else
                {
                    moves.push_back(std::make_unique<IChessMove>(
                        from, captureRight, ChessMoveType::Normal));
                }
            }
        }

        const auto lastMove = board.getLastMove();

        if (lastMove &&
            lastMove->getMoveType() == ChessMoveType::PawnDoubleMove)
        {
            const auto lastTo = lastMove->getTo();

            if (lastTo.row == from.row &&
                (lastTo.col == from.col - 1 || lastTo.col == from.col + 1))
            {
                auto target = board.getPieceAt(lastTo);

                if (target &&
                    target->getType() == ChessPieceType::Pawn &&
                    target->getColor() != piece.getColor())
                {
                    Position enPassantTo{
                        from.row + direction,
                        lastTo.col
                    };

                    if (board.isInside(enPassantTo) && !board.getPieceAt(enPassantTo))
                    {
                        moves.push_back(std::make_unique<IChessMove>(
                            from, enPassantTo, ChessMoveType::EnPassant));
                    }
                }
            }
        }

        return moves;
    }
}