#include "domain/move/chessmove/validator/basic_move_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

namespace boardgame::move::chess
{
    bool BasicMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        if (!board.isInside(move.getFrom()) || !board.isInside(move.getTo()))
        {
            return false;
        }

        if (move.getFrom() == move.getTo())
        {
            return false;
        }

        if (board.getPieceAt(move.getFrom()) == nullptr)
        {
            return false;
        }

        if (
            utils::isDestinationOccupiedByOwnPiece(board, move) &&
            move.getMoveType() != ChessMoveType::EnPassant
        )
        {
            return false;
        }

        return true;
    }
}